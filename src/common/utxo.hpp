#pragma once

// System includes
#include <cstdint>

// Project includes
#include "crypto/address.hpp"
#include "coin_amount.hpp"
#include "color.hpp"
#include "utxoid.hpp"

namespace ech
{

// TODO refactor this as outpoint from transaction
class UTXO
{
private:
	// ID of the UTXO, determined by its hash
	const UTXOID _id;
	// Owner of the UTXO
	const crypto::Address _owner;
	// Amount of coins for this UTXO
	const CoinAmount _amount;
	// Color (if the UTXO represents a colored coin)
	const Color _color;

	[[nodiscard]] const std::vector<std::byte> serializeData(const crypto::Address& owner, const CoinAmount amount, const Color& color) const;

public:
	UTXO(const crypto::Address& owner, const CoinAmount amount, const Color& color);

	[[nodiscard]] const auto& getId() const { return this->_id; }

	[[nodiscard]] const auto& getOwner() const { return this->_owner; }

	[[nodiscard]] const auto getAmount() const { return this->_amount; }

	[[nodiscard]] const auto isColored() const { return this->_color.isColored(); }
};

} // namespace ech