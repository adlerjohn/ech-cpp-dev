#pragma once

// System includes
#include <string>

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

public:
	explicit Signature(const std::string& data);

	bool verify(const std::string& msg, const PublicKey& publicKey) const;
};

} // namespace ech::crypto