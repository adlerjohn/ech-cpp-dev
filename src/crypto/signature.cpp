#include "signature.hpp"

using namespace ech::crypto;

Signature::Signature(std::string data) :
	_data(std::move(data))
{
}

bool Signature::verify(std::string msg, PublicKey publicKey) const
{
	return false;
}