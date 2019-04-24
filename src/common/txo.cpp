#include "txo.hpp"

// Project includes
#include "deserializer.hpp"
#include "serializer.hpp"

using namespace ech;

TXO::TXO(const uint32_t index, const crypto::Address& recipient, const CoinAmount amount, const Color& color)
	: _index(index)
	, _recipient(recipient)
	, _amount(amount)
	, _color(color)
{
}

const TXO TXO::deserialize(std::deque<std::byte>& serial)
{
	const auto index = deserializer::deserialize<uint32_t, 4u>(serial);

	const auto address = deserializer::move<crypto::Address>(serial);

	const auto amount = deserializer::deserialize<CoinAmount, 32u>(serial);

	const auto color = Color::deserialize(serial);

	return TXO(index, address, amount, color);
}

const std::vector<std::byte> TXO::serialize() const
{
	std::vector<std::byte> serial;

	const auto indexBytes = serializer::serialize<uint32_t, 4u>(_index);
	serial.insert(serial.end(), indexBytes.begin(), indexBytes.end());

	serial.insert(serial.end(), _recipient.begin(), _recipient.end());

	const auto amountBytes = serializer::serialize<CoinAmount, 32u>(_amount);
	serial.insert(serial.end(), amountBytes.begin(), amountBytes.end());

	const auto color = _color.serialize();
	serial.insert(serial.end(), color.begin(), color.end());

	return serial;
}