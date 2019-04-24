#include "deposit.hpp"

// Project includes
#include "serializer.hpp"

using namespace ech;

const std::vector<std::byte> Deposit::serializeData(const crypto::Address& owner, const CoinAmount amount, const Color& color, const uint64_t height, const uint64_t nonce)
{
	std::vector<std::byte> serial;

	serial.insert(serial.end(), owner.begin(), owner.end());

	const auto amountBytes = serializer::serialize<CoinAmount, 32u>(amount, true);
	serial.insert(serial.end(), amountBytes.begin(), amountBytes.end());

	const auto colorSerial = color.serialize();
	serial.insert(serial.end(), colorSerial.begin(), colorSerial.end());

	const auto heightBytes = serializer::serialize<uint64_t, 8u>(height);
	serial.insert(serial.end(), heightBytes.begin(), heightBytes.end());

	const auto nonceBytes = serializer::serialize<uint64_t, 8u>(nonce);
	serial.insert(serial.end(), nonceBytes.begin(), nonceBytes.end());

	return serial;
}

Deposit::Deposit(const crypto::Address& owner, const CoinAmount amount, const Color& color, const uint64_t height, const uint64_t nonce)
	: _source(serializeData(owner, amount, color, height, nonce))
	, _owner(owner)
	, _amount(amount)
	, _color(color)
	, _height(height)
	, _nonce(nonce)
{
	// TODO double-check source
}

const std::vector<std::byte> Deposit::serialize() const
{
	std::vector<std::byte> serial;

	serial.insert(serial.end(), _source.begin(), _source.end());

	const auto serialData = serializeData(_owner, _amount, _color, _height, _nonce);
	serial.insert(serial.end(), serialData.begin(), serialData.end());

	return serial;
}