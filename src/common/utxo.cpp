#include "utxo.hpp"

using namespace ech;

const std::vector<std::byte> UTXO::serializeData(const crypto::Address& owner, const CoinAmount amount, const Color& color) const
{
	std::vector<std::byte> serial;

	serial.insert(serial.end(), owner.begin(), owner.end());

	static const size_t amountSize = 32u;
	std::stringstream buf;
	buf << std::hex << std::setfill('0') << std::setw(amountSize * 2) << amount;
	auto str = buf.str();
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	const auto amountBytes = crypto::byteset<amountSize>(str);
	serial.insert(serial.end(), amountBytes.begin(), amountBytes.end());

	const auto colorSerialized = color.serialize();
	serial.insert(serial.end(), colorSerialized.begin(), colorSerialized.end());

	return serial;
}

UTXO::UTXO(const crypto::Address& owner, const CoinAmount amount, const Color& color)
	: _id(UTXOID(serializeData(owner, amount, color)))
	, _owner(owner)
	, _amount(amount)
	, _color(color)
{
}