#include "keys.hpp"

// System includes
#include <iomanip>
#include <sstream>

// Library includes
#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>

using namespace ech::crypto;

SecretKey::SecretKey(const std::string& str)
	: ByteSet(str)
{
}

std::string SecretKey::sign(const Digest& msg) const
{
	// Our secret key is actually the exponent, need to convert
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey sk;
	auto exp = std::string("0x" + this->toHex());
	CryptoPP::Integer x(exp.c_str());
	sk.Initialize(CryptoPP::ASN1::secp256k1(), x);

	// TODO deterministic k!
	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Signer signer(sk);
	bool result = signer.AccessKey().Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid secret key");

	// Decode the message digest from its hex representation since crypto++
	// doesn't support std::byte
	std::string decoded;
	CryptoPP::StringSource(msg.toHex(), true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decoded)
		)
	);

	// Sign the digest using the secret key
	std::string sig;
	CryptoPP::StringSource(decoded, true,
		new CryptoPP::SignerFilter(prng, signer,
			new CryptoPP::StringSink(sig)
		)
	);

	// Encode the signed output to hex
	std::string hexSig;
	CryptoPP::StringSource(sig, true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(hexSig),
			false)
	);

	// TODO should this instead be the Y of the ephemeral public key?
	// hexSig now contains r and s, we need to append v
	// From the Y coordinate of our point:
	// The value 27/35 represents an even Y value and 28/36 represents an odd Y value
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pk;
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

	return hexSig;
}

std::string SecretKey::sign(const std::string& str) const
{
	return sign(Digest(str));
}

auto PublicKey::deriveFromSecretKey(const SecretKey& secretKey)
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey sk;
	auto exp = std::string("0x" + secretKey.toHex());
	CryptoPP::Integer x(exp.c_str());
	sk.Initialize(CryptoPP::ASN1::secp256k1(), x);

	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Signer signer(sk);
	bool result = signer.AccessKey().Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid secret key");

	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pk;
	sk.MakePublicKey(pk);
	result = pk.Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid public key");

	auto e = pk.GetPublicElement();
	std::stringstream buf;
	buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(e.x, 16u);
	buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(e.y, 16u);
	auto publicKey = buf.str();

	return PublicKey(publicKey);
}

auto PublicKey::deterministicK(const Digest& msg, const SecretKey& secretKey)
{
	//auto v_0 = CryptoPP::Integer(std::string(32, "01")));
	auto k = CryptoPP::Integer(std::string("0x00").c_str());
	return k;
}

auto PublicKey::deterministicK(const std::string& str, const SecretKey& secretKey)
{
	return deterministicK(Digest(str), secretKey);
}

PublicKey::PublicKey(const std::string& str)
	: ByteSet(str)
{
}

PublicKey::PublicKey(const SecretKey& secretKey)
	: ByteSet(deriveFromSecretKey(secretKey))
{
}