#include "signature.hpp"

// Library includes
#include <crypto++/eccrypto.h>
#include <crypto++/oids.h>
#include <crypto++/osrng.h>

using namespace ech::crypto;

using namespace CryptoPP;

auto Signature::toSigData(const std::string& data) const
{
	if (data.length() != SIGNATURE_BYTES * 8)
		throw std::invalid_argument("Signature must be exactly " + std::to_string(SIGNATURE_BYTES) + " bytes long.");
	// TODO convert string to SigData
	return SigData();
}

Signature::Signature(SigData data)
	: _data(std::move(data))
{
}

Signature::Signature(const std::string& data)
	: _data(toSigData(data))
{
}

bool Signature::verify(const std::string& msg, const PublicKey& publicKey) const
{
	//using PublicKey = CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey;
	//using SecretKey = CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey;

	/*
	//publicKey.Load();
	ECDSA<ECP, SHA256>::Verifier verifier(publicKey);
	auto result = false;

	StringSource ss(_data + msg, true,
		new SignatureVerificationFilter(
			verifier,
			new ArraySink((byte *) &result, sizeof(result))
		)
	);

	return result;
	 */
	return false;
}