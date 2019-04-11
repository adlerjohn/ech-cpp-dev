#include "signature.hpp"

using namespace ech::crypto;

Signature::Signature(std::string data)
	: _data(std::move(data))
{
	assert(this->_data.length() == SIGNATURE_BYTES * 8);
}

bool Signature::verify(std::string msg, PublicKey publicKey) const
{
	return false;
}