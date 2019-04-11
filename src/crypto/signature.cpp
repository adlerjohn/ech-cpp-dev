#include "signature.hpp"

using namespace ech::crypto;

Signature::Signature(std::string data)
	: _data(std::move(data))
{
	if (this->_data.length() != SIGNATURE_BYTES * 8)
		throw std::invalid_argument("Signature must be exactly " + std::to_string(SIGNATURE_BYTES) + " bytes long.");
}

bool Signature::verify(std::string msg, PublicKey publicKey) const
{
	return false;
}