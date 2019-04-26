#pragma once

// Project includes
#include "crypto/address.hpp"
#include "serializable.hpp"

namespace ech
{

/**
 * Coins can be "colored" i.e., represent a token other than the base currency.
 * Color is the address of the token contract on the parent chain.
 */
class Color : public Serializable
{
private:
	bool _isColored;
	crypto::Address _id;

public:
	Color();

	explicit Color(const crypto::Address& id);

	[[nodiscard]] static const Color deserialize(std::deque<std::byte>& serial);

	const auto isColored() const { return this->_isColored; }
	const auto& getColor() const { return this->_id; }

	/**
	 * Encoding:
	 *   1  byte  boolean : Is this coin colored?
	 *  if above is true,
	 *   20 bytes Address : Address of the token contract on the parent chain.
	 * @return serialized data
	 */
	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech