#pragma once

// System includes
#include <cstdint>

// Project includes
#include "coin_amount.hpp"
#include "color.hpp"
#include "crypto/address.hpp"
#include "serializable.hpp"
#include "utxoid.hpp"

namespace ech
{

class UTXO : public Serializable
{
private:
	// ID of the UTXO, determined by the hash of its outpoint
	UTXOID _id;
	// Outpoint of this UTXO
	Outpoint _outpoint;
	// Owner of the UTXO
	crypto::Address _owner;
	// Amount of coins for this UTXO
	CoinAmount _amount;
	// Color (if the UTXO represents a colored coin)
	Color _color;
	// Height of the transaction that created this UTXO
	uint64_t _height;

public:
	UTXO(const Outpoint& outpoint, const crypto::Address& owner, const CoinAmount amount, const Color& color, const uint64_t height);

	[[nodiscard]] static const UTXO deserialize(std::deque<std::byte>& serial);

	[[nodiscard]] const auto& getId() const { return this->_id; }
	[[nodiscard]] const auto& getOutpoint() const { return this->_outpoint; }
	[[nodiscard]] const auto& getOwner() const { return this->_owner; }
	[[nodiscard]] const auto getAmount() const { return this->_amount; }
	[[nodiscard]] const auto isColored() const { return this->_color.isColored(); }
	[[nodiscard]] const auto& getColor() const { return this->_color; }
	[[nodiscard]] const auto getHeight() const { return this->_height; }

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech