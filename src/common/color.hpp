#pragma once

// Project includes
#include "crypto/address.hpp"

namespace ech
{

/**
 * Coins can be "colored" i.e., represent a token other than the base currency.
 * Color is the address of the token contract on the parent chain.
 */
class Color
{
private:
	const bool _isColored;
	const crypto::Address _id;
public:
	Color();

	Color(crypto::Address id);

	auto isColored() const { return this->_isColored; }

	auto getColor() const { return this->_id; }
};

} // namespace ech