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
#define SIGNATURE_BYTES  65u

namespace ech::crypto
{

class Signature : public byteset<SIGNATURE_BYTES>
{
private:
	static const secp256k1_context* getContextSign();
	static const secp256k1_context* getContextVerify();
	auto sign(const SecretKey& secretKey, const std::string& msg) const;

public:
	explicit Signature(const std::string& sig);

	Signature(const SecretKey& secretKey, const std::string& msg);

	// Recover the public key from the signed message
	PublicKey recover(const std::string& msg) const;

	// Verify that the signature matches the original message
	bool verify(const std::string& msg, const Address& address) const;

	bool verify(const std::string& msg, const PublicKey& publicKey) const;
};

} // namespace ech::crypto