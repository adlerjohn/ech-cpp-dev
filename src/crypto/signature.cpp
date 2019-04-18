#include "signature.hpp"

// System includes
#include <iomanip>

// Library includes
#include <cryptopp/eccrypto.h>
#include <cryptopp/keccak.h>
#include <cryptopp/modarith.h>
#include <cryptopp/nbtheory.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>

using namespace ech::crypto;

Signature::Signature(const std::string& sig)
	: ByteSet(sig)
{
}

Signature::Signature(const std::string& str, const SecretKey& secretKey)
	: Signature(secretKey.sign(str))
{
}

PublicKey Signature::recover(const std::string& msg) const
{
	const auto digest = Digest(msg);

	const auto sig = this->toHex();
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
	CryptoPP::AutoSeededRandomPool prng;
	bool result = pk.Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid public key");

	const auto point = pk.GetPublicElement();
	std::stringstream buf;
	buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(point.x, 16u);
	buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(point.y, 16u);
	const auto publicKey = buf.str();

	return PublicKey(publicKey);
}

bool Signature::verify_direct(const std::string& msg, const PublicKey& publicKey) const
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
	auto hexSig = this->toHex().substr(0, (Signature::size() - 1) * 2);

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

bool Signature::verify(const std::string& msg, const Address& address) const
{
	return Address(recover(msg)) == address;
}

bool Signature::verify(const std::string& msg, const PublicKey& publicKey) const
{
	return verify(msg, Address(publicKey));
}