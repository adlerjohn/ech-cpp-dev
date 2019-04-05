#pragma once

// System includes
#include <cstdint>

// Project includes
#include "address.hpp"
#include "coin_amount.hpp"
#include "color.hpp"

class UTXO
{
private:
	// ID of the UTXO, determined by its hash
	// TODO replace with digest class
	const uint64_t _id;

	// Owner of the UTXO
	const Address _owner;

	// Amount of coins for this UTXO
	const CoinAmount _amount;

	// Color (if the UTXO represents a colored coin)
	const Color _color;

public:
	UTXO();

	uint64_t getId() const;

	Address getOwner() const;

	CoinAmount getAmount() const;

	bool isColored() const;
};