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

PublicKey Signature::recover() const
{
	return PublicKey(std::string(PublicKey::size()*2, '0'));
}

bool Signature::verify(const std::string& msg, const PublicKey& publicKey) const
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pk;
	pk.AccessGroupParameters().Initialize(CryptoPP::ASN1::secp256k1());

	auto hexPublicKey = publicKey.toHex();
	auto px = std::string("0x" + hexPublicKey.substr(0, 64));
	auto py = std::string("0x" + hexPublicKey.substr(64, 64));
	auto point = CryptoPP::ECPPoint(CryptoPP::Integer(px.c_str()), CryptoPP::Integer(py.c_str()));
	pk.SetPublicElement(point);

	// TODO validate this public key!

	// Slice off V from signature
	auto sig = this->toHex();
	sig = sig.substr(sig.length() - 2);
	std::cout << sig.length() << " " << sig << std::endl;

	// Verify
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Verifier verifier(pk);
	auto result = false;
	CryptoPP::StringSource(sig + msg, true,
		new CryptoPP::SignatureVerificationFilter(verifier,
			new CryptoPP::ArraySink((byte*) &result, sizeof(result))
		)
	);

	return result;
}

bool Signature::verify(const std::string& msg) const
{
	return verify(msg, recover());
}