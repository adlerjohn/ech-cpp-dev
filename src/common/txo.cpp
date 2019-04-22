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

	serial.push_back(static_cast<std::byte>(_index));

	serial.insert(serial.end(), _recipient.begin(), _recipient.end());

	static const size_t amountSize = 32u;
	std::stringstream buf;
	buf << std::hex << std::setfill('0') << std::setw(amountSize * 2) << _amount;
	auto str = buf.str();
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	const auto amount = crypto::byteset<amountSize>(str);
	serial.insert(serial.end(), amount.begin(), amount.end());

	const auto color = _color.serialize();
	serial.insert(serial.end(), color.begin(), color.end());

	return serial;
}