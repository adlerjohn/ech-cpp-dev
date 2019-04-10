#pragma once

// System includes
#include <string>

// Project includes
#include "address.hpp"

class Signature
{
private:
	const std::string _data;
public:
	Signature(std::string data);

	std::string getPubKey() const;
	Address getAddress() const;
};