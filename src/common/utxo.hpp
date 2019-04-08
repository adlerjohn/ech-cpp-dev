#pragma once

// System includes
#include <cstdint>

// Project includes
#include "crypto/address.hpp"
#include "coin_amount.hpp"
#include "color.hpp"
#include "utxoid.hpp"

class UTXO
{
private:
	// ID of the UTXO, determined by its hash
	const UTXOID _id;

	// Owner of the UTXO
	const Address _owner;

	// Amount of coins for this UTXO
	const CoinAmount _amount;

	// Color (if the UTXO represents a colored coin)
	const Color _color;

public:
	UTXO();

	UTXOID getId() const;

	Address getOwner() const;

	CoinAmount getAmount() const;

	bool isColored() const;
};