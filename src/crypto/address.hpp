#pragma once

// Project includes
#include "keys.hpp"

#define ADDRESS_BYTES 20u

namespace ech::crypto
{

using PublicKeyAddress = byteset<ADDRESS_BYTES>;

/**
 * Addresses are the last 20 bytes of the Keccak-256 of the hex
 * representation of the public key.
 */
class Address
{
private:
	const PublicKeyAddress _addr;

	auto toAddress(const PublicKey& pk) const;

	auto toAddress(const std::string& pk) const;

public:
	explicit Address(const std::string& pk);

	explicit Address(const PublicKey& pk);

	static auto addressBytes() { return ADDRESS_BYTES; }

	auto getAddress() const { return this->_addr; }

	friend std::ostream& operator<<(std::ostream& os, const Address& o)
	{
		os << o.getAddress();
		return os;
	}
};

} // namespace ech::crypto