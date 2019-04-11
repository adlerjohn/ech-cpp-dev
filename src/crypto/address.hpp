#pragma once

// System includes
#include <bitset>

// Project includes
#include "keys.hpp"

#define ADDRESS_BYTES 20

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

	auto toAddress(const std::string& pk) const;

	auto toAddress(const PublicKey& pk) const;

public:
	explicit Address(const std::string& pk);

	explicit Address(const PublicKey& pk);

	auto getAddress() const { return this->_addr; }
};

} // namespace ech::crypto