#pragma once

// Project includes
#include "coin_amount.hpp"
#include "color.hpp"
#include "crypto/address.hpp"
#include "serializable.hpp"

namespace ech
{

class TXO : public Serializable
{
private:
	const uint32_t _index;
	crypto::Address _recipient;
	const CoinAmount _amount;
	const Color _color;

public:
	TXO(const uint32_t index, const crypto::Address& recipient, const CoinAmount amount, const Color& color);

	[[nodiscard]] static const TXO deserialize(std::deque<std::byte>& serial);

	[[nodiscard]] const auto getIndex() const { return this->_index; }
	[[nodiscard]] const auto getRecipient() const { return this->_recipient; }
	[[nodiscard]] const auto getAmount() const { return this->_amount; }
	[[nodiscard]] const auto getColor() const { return this->_color; }

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech