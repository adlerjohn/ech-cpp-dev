#include "signer.hpp"

// System includes
#include <iomanip>
// TODO remove
#include <iostream>
#include <sstream>

// Library includes
#include <secp256k1_recovery.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/keccak.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>

using namespace ech::crypto;

bool Signer::verify(const Signature& signature, const std::string& msg, const Address& address) const
{
	return Address(recover(signature, msg)) == address;
}

bool Signer::verify(const Signature& signature, const std::string& msg, const PublicKey& publicKey) const
{
	return verify(signature, msg, Address(publicKey));
}

Signature Signer_CryptoPP::sign(const SecretKey& secretKey, const std::string& msg) const
{
	// Our secret key is actually the exponent, need to convert
	CryptoPP::ECDSA_RFC6979<CryptoPP::ECP, CryptoPP::Keccak_256>::PrivateKey sk;
	const auto x = CryptoPP::Integer(std::string("0x" + secretKey.toHex()).c_str());
	sk.Initialize(CryptoPP::ASN1::secp256k1(), x);

	// Validate secret key
	CryptoPP::AutoSeededRandomPool prng;
	bool result = sk.Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid secret key");

	// Sign the message using the secret key
	std::string sig;
	CryptoPP::ECDSA_RFC6979<CryptoPP::ECP, CryptoPP::Keccak_256>::Signer signer(sk);
	CryptoPP::StringSource(msg, true,
		new CryptoPP::SignerFilter(CryptoPP::NullRNG(), signer,
			new CryptoPP::StringSink(sig)
		)
	);

	// Encode the signed output to hex
	std::string hexSig;
	CryptoPP::StringSource(sig, true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(hexSig),
			false
		)
	);

	// TODO should this instead be the Y of the ephemeral public key?
	// hexSig now contains r and s, we need to append v
	// From the Y coordinate of our point:
	// The value 27/35 represents an even Y value and 28/36 represents an odd Y value
	CryptoPP::ECDSA_RFC6979<CryptoPP::ECP, CryptoPP::Keccak_256>::PublicKey pk;
	sk.MakePublicKey(pk);
	result = pk.Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid public key");

	auto point = pk.GetPublicElement();
	// Hex representations of 27 and 28 are 0x1b and 0x1c
	auto v = (point.y % 2 == 0) ? std::string("1b") : std::string("1c");
	// Hex representations of 35 and 36 are 0x23 and 0x24
	//auto v = (point.y % 2 == 0) ? std::string("23") : std::string("24");
	hexSig += v;

	return Signature(hexSig);
}

PublicKey Signer_CryptoPP::recover(const Signature& signature, const std::string& msg) const
{
	const auto digest = Digest(msg);

	const auto sig = signature.toHex();
	const auto r = sig.substr(0, 64);
	const auto s = sig.substr(64, 64);
	const auto v = sig.substr(128, 2);

	const auto ri = CryptoPP::Integer(std::string("0x" + r).c_str());
	const auto si = CryptoPP::Integer(std::string("0x" + s).c_str());
	const auto vi = CryptoPP::Integer(std::string("0x" + v).c_str());
	const auto di = CryptoPP::Integer(std::string("0x" + digest.toHex()).c_str());

	CryptoPP::ECDSA_RFC6979<CryptoPP::ECP, CryptoPP::Keccak_256>::PublicKey pk;
	pk.AccessGroupParameters().Initialize(CryptoPP::ASN1::secp256k1());

	const auto curve = pk.GetGroupParameters().GetCurve();
	// Field size
	const auto P = curve.FieldSize();
	// A
	const auto A = curve.GetA();
	// B
	const auto B = curve.GetB();
	// Curve generator point coordinates
	const auto G = pk.GetGroupParameters().GetSubgroupGenerator();
	// Group order
	const auto N = pk.GetGroupParameters().GetGroupOrder();

	// r is the x coordinate of the ephemeral public key
	const auto compactPoint = std::string((vi % 2 == 1 ? "02" : "03") + r);
	CryptoPP::StringSource source(compactPoint, true, new CryptoPP::HexDecoder);
	CryptoPP::ECP::Point R;
	curve.DecodePoint(R, source, source.MaxRetrievable());

	// K = ri^-1 * (sR - zG)
	// Calculate each term multiplied by ri^-1, then add them
	const auto ri_inv = ri.InverseMod(N);

	// ri^-1 * sR
	const auto s_inv = ri_inv.Times(si).Modulo(N);
	const auto sR = curve.ScalarMultiply(R, s_inv);

	// ri^-1 * -zG
	auto e = di;
	e.Negate();
	e.Modulo(N);
	const auto z = e.Times(ri_inv).Modulo(N);
	const auto minuszG = curve.ScalarMultiply(G, z);

	const auto K = curve.Add(sR, minuszG);

	pk.SetPublicElement(K);

	// Validate public key
	// Do level-1 checks because level-2 or level-3 checks take too long
	CryptoPP::AutoSeededRandomPool prng;
	bool result = pk.Validate(prng, 1);
	if (!result)
		throw std::runtime_error("invalid public key");

	const auto point = pk.GetPublicElement();
	std::stringstream buf;
	buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(point.x, 16u);
	buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(point.y, 16u);
	const auto publicKey = buf.str();

	return PublicKey(publicKey);
}

bool Signer_CryptoPP::verify_direct(const Signature& signature, const std::string& msg, const PublicKey& publicKey) const
{
	CryptoPP::ECDSA_RFC6979<CryptoPP::ECP, CryptoPP::Keccak_256>::PublicKey pk;
	pk.AccessGroupParameters().Initialize(CryptoPP::ASN1::secp256k1());

	auto hexPublicKey = publicKey.toHex();
	auto px = std::string("0x" + hexPublicKey.substr(0, PublicKey::size()));
	auto py = std::string("0x" + hexPublicKey.substr(PublicKey::size(), PublicKey::size()));
	auto point = CryptoPP::ECPPoint(CryptoPP::Integer(px.c_str()), CryptoPP::Integer(py.c_str()));
	pk.SetPublicElement(point);

	// Validate public key
	CryptoPP::AutoSeededRandomPool prng;
	bool result = pk.Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid public key");

	// Slice off v from signature
	auto hexSig = signature.toHex().substr(0, (Signature::size() - 1) * 2);

	std::string decodedSignature;
	CryptoPP::StringSource(hexSig, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decodedSignature)
		)
	);

	// Verify
	CryptoPP::ECDSA_RFC6979<CryptoPP::ECP, CryptoPP::Keccak_256>::Verifier verifier(pk);
	CryptoPP::StringSource(decodedSignature + msg, true,
		new CryptoPP::SignatureVerificationFilter(verifier,
			new CryptoPP::ArraySink((CryptoPP::byte*) &result, sizeof(result))
		)
	);

	return result;
}

const secp256k1_context* Signer_libsecp256k1::getContextSign()
{
	static std::unique_ptr<secp256k1_context, decltype(&secp256k1_context_destroy)> context(secp256k1_context_create(SECP256K1_CONTEXT_SIGN), &secp256k1_context_destroy);
	return context.get();
}

const secp256k1_context* Signer_libsecp256k1::getContextVerify()
{
	static std::unique_ptr<secp256k1_context, decltype(&secp256k1_context_destroy)> context(secp256k1_context_create(SECP256K1_CONTEXT_VERIFY), &secp256k1_context_destroy);
	return context.get();
}

Signature Signer_libsecp256k1::sign(const SecretKey& secretKey, const std::string& msg) const
{
	auto context = getContextSign();

	auto digest = Digest(msg);
	secp256k1_ecdsa_recoverable_signature sig;
	if (!secp256k1_ecdsa_sign_recoverable(context, &sig, reinterpret_cast<const unsigned char*>(digest.data().data()), reinterpret_cast<const unsigned char*>(secretKey.data().data()), nullptr, nullptr))
		throw std::runtime_error("Could not sign message: " + msg);

	std::array<std::byte, 64u> rs;
	int v = 0;
	secp256k1_ecdsa_recoverable_signature_serialize_compact(context, reinterpret_cast<unsigned char *>(rs.data()), &v, &sig);
	v += 27;

	std::stringstream buf;
	buf << std::hex << std::setfill('0');
	for (auto c : rs)
		buf << std::setw(2) << static_cast<int>(c);
	buf << std::setw(2) << v;

	return Signature(buf.str());
}

PublicKey Signer_libsecp256k1::recover(const Signature& signature, const std::string& msg) const
{
	auto context = getContextVerify();

	const auto v_hex = signature.toHex().substr(128, 2);
	std::stringstream buf;
	buf << std::hex << v_hex;
	int v;
	buf >> v;
	v -= 27;

	const auto digest = Digest(msg);
	secp256k1_ecdsa_recoverable_signature sig;
	if (!secp256k1_ecdsa_recoverable_signature_parse_compact(context, &sig, reinterpret_cast<const unsigned char*>(signature.data().data()), v))
		throw std::runtime_error("Could not parse signature: " + signature.toHex());

	secp256k1_pubkey pubkey;
	if (!secp256k1_ecdsa_recover(context, &pubkey, &sig, reinterpret_cast<const unsigned char*>(digest.data().data())))
		throw std::runtime_error("Could recover pubkey from signature: " + signature.toHex());

	std::array<std::byte, 65> pubkey_serialized;
	size_t outputlen = pubkey_serialized.size();
	secp256k1_ec_pubkey_serialize(context, reinterpret_cast<unsigned char*>(pubkey_serialized.data()), &outputlen, &pubkey, SECP256K1_EC_UNCOMPRESSED);

	std::stringstream buf_pubkey;
	buf_pubkey << std::hex << std::setfill('0');
	auto it = pubkey_serialized.begin();
	for (++it; it != pubkey_serialized.end(); ++it)
		buf_pubkey << std::setw(2) << static_cast<int>(*it);

	return PublicKey(buf_pubkey.str());
}

void Signer_libsecp256k1::initialize() const
{
	getContextSign();
	getContextVerify();
}