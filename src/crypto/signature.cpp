#include "signature.hpp"

Signature::Signature(std::string data) :
	_data(std::move(data))
{
}

std::string Signature::getPubKey() const
{
	return std::string();
}

Address Signature::getAddress() const
{
	return Address();
}