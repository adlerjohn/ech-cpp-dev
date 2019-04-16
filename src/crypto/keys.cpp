#include "keys.hpp"

// System includes
#include <iomanip>
#include <sstream>

// Library includes
#include <cryptopp/eccrypto.h>
#include <cryptopp/keccak.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>

using namespace ech::crypto;

SecretKey::SecretKey(const std::string& str)
	: ByteSet(str)
{
}

std::string SecretKey::sign(const std::string& msg) const
{
	// Our secret key is actually the exponent, need to convert
	CryptoPP::ECDSA_RFC6979<CryptoPP::ECP, CryptoPP::Keccak_256>::PrivateKey sk;
	const auto x = CryptoPP::Integer(std::string("0x" + this->toHex()).c_str());
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

	return hexSig;
}

auto PublicKey::deriveFromSecretKey(const SecretKey& secretKey)
{
	CryptoPP::ECDSA_RFC6979<CryptoPP::ECP, CryptoPP::Keccak_256>::PrivateKey sk;
	const auto x = CryptoPP::Integer(std::string("0x" + secretKey.toHex()).c_str());
	sk.Initialize(CryptoPP::ASN1::secp256k1(), x);

	CryptoPP::AutoSeededRandomPool prng;
	bool result = sk.Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid secret key");

	CryptoPP::ECDSA_RFC6979<CryptoPP::ECP, CryptoPP::Keccak_256>::PublicKey pk;
	sk.MakePublicKey(pk);
	result = pk.Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid public key");

	auto point = pk.GetPublicElement();
	std::stringstream buf;
	buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(point.x, 16u);
	buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(point.y, 16u);
	auto publicKey = buf.str();

	return PublicKey(publicKey);
}

PublicKey::PublicKey(const std::string& str)
	: ByteSet(str)
{
}

PublicKey::PublicKey(const SecretKey& secretKey)
	: ByteSet(deriveFromSecretKey(secretKey))
{
}