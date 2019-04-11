#include "address.hpp"

using namespace ech::crypto;

auto Address::toAddress(const std::string& pk) const
{
	// TODO hex
	// TODO keccak
	// TODO slice

	//pk.substr(256-20*8-1);
	return PublicKeyAddress();
}

auto Address::toAddress(const PublicKey& pk) const
{
	// TODO
	return PublicKeyAddress();
}

Address::Address(const std::string& pk)
	: _addr(toAddress(pk))
{
}

Address::Address(const PublicKey& pk)
	: _addr(toAddress(pk))
{
}