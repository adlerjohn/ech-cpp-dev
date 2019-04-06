#pragma once

// Project includes
#include "address.hpp"

/**
 * Coins can be "colored" i.e., represent a token other than the base currency.
 * Color is the address of the token contract on the parent chain.
 */
class Color
{
private:
	const bool _isColored;
	const Address _id;
public:
	Color();
	Color(Address id);

	bool isColored() const;
	Address getColor() const;
};