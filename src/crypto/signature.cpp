#include "signature.hpp"

using namespace ech::crypto;

using namespace CryptoPP;

Signature::Signature(std::string data)
	: _data(std::move(data))
{
	if (this->_data.length() != SIGNATURE_BYTES * 8)
		throw std::invalid_argument("Signature must be exactly " + std::to_string(SIGNATURE_BYTES) + " bytes long.");
}

bool Signature::verify(const std::string& msg, const PublicKey& publicKey) const
{
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
}