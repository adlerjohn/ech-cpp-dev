#pragma once

// System includes
#include <bitset>
#include <iostream>
#include <string>

// Project includes
#include "address.hpp"
#include "keys.hpp"

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