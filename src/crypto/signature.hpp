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

using SigData = byteset<SIGNATURE_BYTES>;

class Signature
{
private:
	const SigData _data;

public:
	explicit Signature(SigData data);

	explicit Signature(const std::string& data);

	static auto signatureBytes() { return SIGNATURE_BYTES; }

	auto data() const { return this->_data; }

	bool verify(const std::string& msg, const PublicKey& publicKey) const;

	friend std::ostream& operator<<(std::ostream& os, const Signature& o)
	{
		os << o.data();
		return os;
	}
};

} // namespace ech::crypto