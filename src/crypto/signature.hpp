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
	Address getSender() const;
};