#include "keys.hpp"

// Library includes
#include <crypto++/eccrypto.h>
#include <crypto++/oids.h>
#include <crypto++/osrng.h>

using namespace ech::crypto;

SecretKey::SecretKey(const std::string& str)
	: ByteSet(str)
{
}

std::string SecretKey::sign(const Digest& msg) const
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey sk;
	auto exp = std::string("0x" + this->toHex());
	CryptoPP::Integer x(exp.c_str());
	sk.Initialize(CryptoPP::ASN1::secp256k1(), x);

	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Signer signer(sk);
	bool result = signer.AccessKey().Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid secret key");

	std::string decoded;
	CryptoPP::StringSource(msg.toHex(), true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decoded)
		)
	);

	std::string sig;
	CryptoPP::StringSource(decoded, true,
		new CryptoPP::SignerFilter(prng, signer,
			new CryptoPP::StringSink(sig)
		)
	);

	std::string hexSig;
	CryptoPP::StringSource(sig, true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(hexSig),
			false)
	);

	return hexSig;
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