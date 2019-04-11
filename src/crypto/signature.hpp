#pragma once

// System includes
#include <bitset>
#include <iostream>
#include <string>

// Project includes
#include "address.hpp"
#include "keys.hpp"

// Signatures are 65 bytes:
//  32 bytes r
//  32 bytes s
//  1  byte  v
#define SIGNATURE_BYTES  65

namespace ech::crypto
{

class Signature
{
private:
	const std::string _data;

public:
	explicit Signature(std::string data);

	auto getData() const { return this->_data; }

	bool verify(std::string msg, PublicKey publicKey) const;

	friend std::ostream& operator<<(std::ostream& os, const Signature& o)
	{
		// TODO need to convert to hex
		os << o.getData();
		return os;
	}
};

} // namespace ech::crypto