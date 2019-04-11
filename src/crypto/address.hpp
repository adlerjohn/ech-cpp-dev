#pragma once

// System includes
#include <bitset>

// Project includes
#include "keys.hpp"

namespace ech::crypto
{

/**
 * Addresses are the last 20 bytes of the Keccak-256 of the hex
 * representation of the public key.
 */
class Address
{
private:
	const std::string _addr;

	auto keyToAddress(std::string pk) const;

	auto keyToAddress(PublicKey pk) const;

public:
	explicit Address(std::string pk);

	explicit Address(PublicKey pk);

	auto getAddress() const { return this->_addr; }
};

} // namespace ech::crypto