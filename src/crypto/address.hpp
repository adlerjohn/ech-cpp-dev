#pragma once

// Project includes
#include "keys.hpp"

#define DEFINE_ADDRESS_BYTES 20u

namespace ech::crypto
{

/**
 * Addresses are the last 20 bytes of the Keccak-256 of the hex
 * representation of the public key.
 */
class Address : public byteset<DEFINE_ADDRESS_BYTES>
{
private:
	[[nodiscard]] static auto toAddress(const PublicKey& publicKey);

public:
	Address();

	explicit Address(const std::array<std::byte, DEFINE_ADDRESS_BYTES>& bytes)
		: ByteSet(bytes)
	{
	}

	explicit Address(const std::string& str);

	explicit Address(const PublicKey& publicKey);
};

} // namespace ech::crypto