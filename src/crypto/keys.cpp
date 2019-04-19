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

const secp256k1_context* PublicKey::getContextKeys()
{
	static std::unique_ptr<secp256k1_context, decltype(&secp256k1_context_destroy)> context(secp256k1_context_create(SECP256K1_CONTEXT_NONE), &secp256k1_context_destroy);
	return context.get();
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

	const auto& point = pk.GetPublicElement();
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