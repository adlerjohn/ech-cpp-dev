#include "txo.hpp"

// Project includes
#include "serializer.hpp"

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

	const auto indexBytes = serializer::serialize<uint32_t, 4u>(_index);
	serial.insert(serial.end(), indexBytes.begin(), indexBytes.end());

	serial.insert(serial.end(), _recipient.begin(), _recipient.end());

	const auto amountBytes = serializer::serialize<CoinAmount, 32u>(_amount, true);
	serial.insert(serial.end(), amountBytes.begin(), amountBytes.end());

	const auto color = _color.serialize();
	serial.insert(serial.end(), color.begin(), color.end());

	return serial;
}