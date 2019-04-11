#include "address.hpp"

using namespace ech::crypto;

auto Address::keyToAddress(std::string pk) const
{
	// TODO hex
	// TODO keccak
	// TODO slice

	//pk.substr(256-20*8-1);
	return std::string();
}

auto Address::keyToAddress(PublicKey pk) const
{
	return std::string();
}

Address::Address(std::string pk)
	: _addr(keyToAddress(pk))
{
}

Address::Address(PublicKey pk)
	: _addr(keyToAddress(pk))
{
}