#pragma once

// Project includes
#include "coin_amount.hpp"
#include "color.hpp"
#include "crypto/address.hpp"

namespace ech
{

class TXO
{
private:
	const uint32_t _index;
	crypto::Address _recipient;
	const CoinAmount _amount;
	const Color _color;

public:
};

} // namespace ech