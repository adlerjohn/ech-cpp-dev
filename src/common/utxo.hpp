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

class UTXO
{
private:
	// ID of the UTXO, determined by the hash of its outpoint
	const UTXOID _id;
	// Owner of the UTXO
	const crypto::Address _owner;
	// Amount of coins for this UTXO
	const CoinAmount _amount;
	// Color (if the UTXO represents a colored coin)
	const Color _color;
	// Height of the transaction that created this UTXO
	const uint64_t _height;

public:
	UTXO(const UTXOID& id, const crypto::Address& owner, const CoinAmount amount, const Color& color, const uint64_t height);

	[[nodiscard]] const auto& getId() const { return this->_id; }

	[[nodiscard]] const auto& getOwner() const { return this->_owner; }

	[[nodiscard]] const auto getAmount() const { return this->_amount; }

	[[nodiscard]] const auto isColored() const { return this->_color.isColored(); }

	[[nodiscard]] const auto& getColor() const { return this->_color; }

	[[nodiscard]] const auto getHeight() const { return this->_height; }
};

} // namespace ech