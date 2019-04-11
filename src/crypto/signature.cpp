#include "signature.hpp"

// Library includes
#include <crypto++/eccrypto.h>
#include <crypto++/oids.h>
#include <crypto++/osrng.h>

using namespace ech::crypto;

using namespace CryptoPP;

Signature::Signature(SigData data)
	: _data(std::move(data))
{
}

Signature::Signature(const std::string& data)
	: _data(SigData(data))
{
}

bool Signature::verify(const std::string& msg, const PublicKey& publicKey) const
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pk;

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