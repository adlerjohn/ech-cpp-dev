#pragma once

// System includes
#include <string>

// Project includes
#include "address.hpp"
#include "keys.hpp"
#include "crypto/signer.hpp"

// Signatures are 65 bytes:
//  32 bytes r
//  32 bytes s
//  1  byte  v
#define SIGNATURE_BYTES  65u

namespace ech::crypto
{

class Signer;

class Signature : public byteset<SIGNATURE_BYTES>
{
private:
public:
	explicit Signature(const std::string& sig);

	Signature(const SecretKey& secretKey, const std::string& str, const Signer& signer);

	// Recover the public key from the signed message
	PublicKey recover(const std::string& msg, const Signer& signer) const;

	// Verify that the signature matches the original message
	bool verify(const std::string& msg, const Address& address, const Signer& signer) const;

	bool verify(const std::string& msg, const PublicKey& publicKey, const Signer& signer) const;
};

} // namespace ech::crypto