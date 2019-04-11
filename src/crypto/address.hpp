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

	auto keyToAddress(const std::string& pk) const;

	auto keyToAddress(const PublicKey& pk) const;

public:
	explicit Address(const std::string& pk);

	explicit Address(const PublicKey& pk);

	auto getAddress() const { return this->_addr; }
};

} // namespace ech::crypto