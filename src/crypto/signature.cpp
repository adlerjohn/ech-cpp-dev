#include "signature.hpp"

// TODO remove
#include <iostream>

// Library includes
#include <crypto++/eccrypto.h>
#include <crypto++/oids.h>
#include <crypto++/osrng.h>

using namespace ech::crypto;

Signature::Signature(const std::string& sig)
	: ByteSet(sig)
{
}

Signature::Signature(const std::string& str, const SecretKey& secretKey)
	: Signature(secretKey.sign(str))
{
}

PublicKey Signature::recover() const
{
	// TODO implement this!
	return PublicKey(std::string(PublicKey::size() * 2, '0'));
}

bool Signature::verify(const Digest& digest, const PublicKey& publicKey) const
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pk;
	pk.AccessGroupParameters().Initialize(CryptoPP::ASN1::secp256k1());

	auto hexPublicKey = publicKey.toHex();
	auto px = std::string("0x" + hexPublicKey.substr(0, PublicKey::size()));
	auto py = std::string("0x" + hexPublicKey.substr(PublicKey::size(), PublicKey::size()));
	auto point = CryptoPP::ECPPoint(CryptoPP::Integer(px.c_str()), CryptoPP::Integer(py.c_str()));
	pk.SetPublicElement(point);

	// TODO validate this public key!

	// Slice off V from signature
	auto hexSig = this->toHex().substr(0, (Signature::size() - 1) * 2);
	std::cout << hexSig.length() << " " << hexSig << std::endl;

	std::string decodedSignature;
	CryptoPP::StringSource(hexSig, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decodedSignature)
		)
	);

	std::string decodedDigest;
	CryptoPP::StringSource(digest.toHex(), true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decodedDigest)
		)
	);

	// Verify
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Verifier verifier(pk);
	auto result = false;
	CryptoPP::StringSource(decodedSignature + decodedDigest, true,
		new CryptoPP::SignatureVerificationFilter(verifier,
			new CryptoPP::ArraySink((byte*) &result, sizeof(result))
		)
	);

	return result;
}

bool Signature::verify(const std::string& msg, const PublicKey& publicKey) const
{
	return verify(Digest(msg), publicKey);
}

bool Signature::verify(const Digest& digest) const
{
	return verify(digest, this->recover());
}

bool Signature::verify(const std::string& msg) const
{
	return verify(Digest(msg));
}