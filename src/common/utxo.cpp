#include "utxo.hpp"

using namespace ech;

UTXO::UTXO(const crypto::Address& owner, const CoinAmount& amount, const Color& color)
	: _id(UTXOID(std::string(64u, '0')))
	, _owner(owner)
	, _amount(amount)
	, _color(color)
{
}