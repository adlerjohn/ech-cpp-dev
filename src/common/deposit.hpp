#pragma once

// Project includes
#include "color.hpp"
#include "serializable.hpp"

namespace ech
{

/**
 * Deposit "transaction" from parent chain.
 */
class Deposit : public Serializable
{
private:
	// Source is the receipt hash from the deposit on the parent chain, which
	// should be identical to the hash of the serialized data here.
	const crypto::Digest _source;
	const crypto::Address _owner;
	const CoinAmount _amount;
	const Color _color;
	const uint64_t _height;
	// Each deposit within a block has a unique nonce, starting at 0 and incrementing
	const uint64_t _nonce;

	[[nodiscard]] static const std::vector<std::byte> serializeData(const crypto::Address& owner, const CoinAmount amount, const Color& color, const uint64_t height, const uint64_t nonce);

public:
	Deposit(const crypto::Address& owner, const CoinAmount amount, const Color& color, const uint64_t height, const uint64_t nonce);

	[[nodiscard]] const auto& getSource() const { return this->_source; }
	[[nodiscard]] const auto& getOwner() const { return this->_owner; }
	[[nodiscard]] const auto getAmount() const { return this->_amount; }
	[[nodiscard]] const auto isColored() const { return this->_color.isColored(); }
	[[nodiscard]] const auto& getColor() const { return this->_color; }
	[[nodiscard]] const auto getHeight() const { return this->_height; }

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech