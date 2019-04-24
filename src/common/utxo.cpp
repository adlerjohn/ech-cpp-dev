#include "utxo.hpp"

// Project includes
#include "deserializer.hpp"
#include "serializer.hpp"

using namespace ech;

UTXO::UTXO(const UTXOID& id, const crypto::Address& owner, const CoinAmount amount, const Color& color, const uint64_t height)
	: _id(id)
	, _owner(owner)
	, _amount(amount)
	, _color(color)
	, _height(height)
{
}

const UTXO UTXO::deserialize(std::deque<std::byte>& serial)
{
	const auto id = deserializer::move<UTXOID>(serial);

	const auto owner = deserializer::move<crypto::Address>(serial);

	const auto amount = deserializer::deserialize<CoinAmount, 32u>(serial);

	const auto color = Color::deserialize(serial);

	const auto height = deserializer::deserialize<uint64_t, 8u>(serial);

	return UTXO(id, owner, amount, color, height);
}

const std::vector<std::byte> UTXO::serialize() const
{
	std::vector<std::byte> serial;

	serial.insert(serial.end(), _id.begin(), _id.end());

	serial.insert(serial.end(), _owner.begin(), _owner.end());

	const auto amountBytes = serializer::serialize<CoinAmount, 32u>(_amount);
	serial.insert(serial.end(), amountBytes.begin(), amountBytes.end());

	const auto colorSerial = _color.serialize();
	serial.insert(serial.end(), colorSerial.begin(), colorSerial.end());

	const auto heightBytes = serializer::serialize<uint64_t, 8u>(_height);
	serial.insert(serial.end(), heightBytes.begin(), heightBytes.end());

	return serial;
}