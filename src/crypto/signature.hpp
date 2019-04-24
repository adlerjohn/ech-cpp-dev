#pragma once

// System includes
#include <string>

// Library includes
#include <secp256k1.h>

// Project includes
#include "address.hpp"
#include "keys.hpp"

// Signatures are 65 bytes:
//  32 bytes r
//  32 bytes s
//  1  byte  v
#define DEFINE_SIGNATURE_BYTES  65u

namespace ech::crypto
{

class Signature : public byteset<DEFINE_SIGNATURE_BYTES>
{
private:
	[[nodiscard]] static const auto getContextSign();

	[[nodiscard]] static const auto getContextVerify();

	[[nodiscard]] static const auto sign(const SecretKey& secretKey, const Digest& digest);

public:
	explicit Signature(const std::string& sig);

	Signature(const SecretKey& secretKey, const std::vector<std::byte>& msg);

	Signature(const SecretKey& secretKey, const std::string& msg);

	// Recover the public key from the signed message
	[[nodiscard]] const PublicKey recover(const Digest& digest) const;

	// Verify that the signature matches the original message
	[[nodiscard]] const bool verify(const Digest& digest, const Address& address) const;
};

} // namespace ech::crypto