#include "signature.hpp"

// System includes
#include <iomanip>

// Library includes
#include <cryptopp/eccrypto.h>
#include <cryptopp/keccak.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>

using namespace ech::crypto;

Signature::Signature(const std::string& sig)
	: ByteSet(sig)
{
}

Signature::Signature(const SecretKey& secretKey, const std::string& str, const Signer& signer = SignerCryptoPP())
	: Signature(signer.sign(secretKey, str))
{
}

PublicKey Signature::recover(const std::string& msg, const Signer& signer = SignerCryptoPP()) const
{
	return signer.recover(*this, msg);
}

bool Signature::verify(const std::string& msg, const Address& address, const Signer& signer) const
{
	return signer.verify(*this, msg, address);
}

bool Signature::verify(const std::string& msg, const PublicKey& publicKey, const Signer& signer) const
{
	return verify(msg, Address(publicKey), signer);
}