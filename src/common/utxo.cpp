#include "utxo.hpp"

using namespace ech;

UTXO::UTXO(const UTXOID& id, const crypto::Address& owner, const CoinAmount amount, const Color& color, const uint64_t height)
	: _id(id)
	, _owner(owner)
	, _amount(amount)
	, _color(color)
	, _height(height)
{
}