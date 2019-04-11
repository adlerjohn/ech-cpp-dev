#include "address.hpp"

using namespace ech::crypto;

auto Address::keyToAddress(const std::string& pk) const
{
	// TODO hex
	// TODO keccak
	// TODO slice

	//pk.substr(256-20*8-1);
	return std::string();
}

auto Address::keyToAddress(const PublicKey& pk) const
{
	// TODO
	return std::string();
}

Address::Address(const std::string& pk)
	: _addr(keyToAddress(pk))
{
}

Address::Address(const PublicKey& pk)
	: _addr(keyToAddress(pk))
{
}