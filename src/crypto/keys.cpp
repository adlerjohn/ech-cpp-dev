#include "keys.hpp"

// Library includes
#include <crypto++/eccrypto.h>
#include <crypto++/oids.h>
#include <crypto++/osrng.h>

// Project includes
//#include "signature.hpp"

using namespace ech::crypto;

SecretKey::SecretKey(const std::string& str)
	: ByteSet(str)
{
}

std::string SecretKey::sign(const Digest& msg) const
{
	// TODO implement
	return std::string("TODO");
}

std::string SecretKey::sign(const std::string& str) const
{
	return sign(Digest(str));
}

auto PublicKey::deriveFromSecretKey(const SecretKey& secretKey) const
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

	std::string publicKey;
	pk.Save(CryptoPP::HexEncoder(new CryptoPP::StringSink(publicKey), false).Ref());
	// TODO is this correct?
	publicKey = publicKey.substr(publicKey.length() - PublicKey::size() * 2u);

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
