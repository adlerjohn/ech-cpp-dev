#include "signature.hpp"

// Library includes
#include <crypto++/eccrypto.h>
#include <crypto++/oids.h>
#include <crypto++/osrng.h>

using namespace ech::crypto;

Signature::Signature(const std::string& data)
	: ByteSet(data)
{
}

bool Signature::verify(const std::string& msg, const PublicKey& publicKey) const
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pk;

	std::string decoded;
	CryptoPP::StringSource(publicKey.toHex(), true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decoded)
		)
	);
	CryptoPP::StringSource source(decoded, true);
	pk.Load(source);

	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Verifier verifier(pk);
	auto result = false;

	CryptoPP::StringSource(this->toHex() + msg, true,
		new CryptoPP::SignatureVerificationFilter(verifier,
			new CryptoPP::ArraySink((byte*) &result, sizeof(result))
		)
	);

	return result;
}