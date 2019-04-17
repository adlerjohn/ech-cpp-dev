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
	// ID of the UTXO, determined by its hash
	const UTXOID _id;

	// Owner of the UTXO
	const crypto::Address _owner;

	// Amount of coins for this UTXO
	const CoinAmount _amount;

	// Color (if the UTXO represents a colored coin)
	const Color _color;

public:
	UTXO(const crypto::Address owner, const CoinAmount& amount, const Color& color);

	auto getId() const { return this->_id; }

	auto getOwner() const { return this->_owner; }

	auto getAmount() const { return this->_amount; }

	auto isColored() const { return this->_color.isColored(); }
};

} // namespace ech