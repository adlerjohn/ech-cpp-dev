#include "txo.hpp"

using namespace ech;

TXO::TXO(const uint32_t index, const crypto::Address& recipient, const CoinAmount amount, const Color& color)
	: _index(index)
	, _recipient(recipient)
	, _amount(amount)
	, _color(color)
{
}

const std::vector<std::byte> TXO::serialize() const
{
	std::vector<std::byte> serial;

	const auto indexBytes = Serializable::serialize(_index);
	serial.insert(serial.end(), indexBytes.begin(), indexBytes.end());

	serial.insert(serial.end(), _recipient.begin(), _recipient.end());

	const auto amountBytes = Serializable::serialize(_amount);
	serial.insert(serial.end(), amountBytes.begin(), amountBytes.end());

	const auto color = _color.serialize();
	serial.insert(serial.end(), color.begin(), color.end());

	return serial;
}