#include "txo.hpp"

using namespace ech;

TXO::TXO(const uint32_t index, const crypto::Address recipient, const CoinAmount amount, const Color& color)
	: _index(index)
	, _recipient(recipient)
	, _amount(amount)
	, _color(color)
{
}

const std::vector<std::byte> TXO::serialize() const
{
	// TODO implement
	return std::vector<std::byte>();
}