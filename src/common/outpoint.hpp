#pragma once

// Project includes
#include "serializable.hpp"
#include "txid.hpp"

namespace ech
{

class Outpoint : public Serializable
{
private:
	TXID _txid;
	uint32_t _index;

public:
	Outpoint(const TXID& txid, const uint32_t index);

	[[nodiscard]] static const Outpoint deserialize(std::deque<std::byte>& serial);

	[[nodiscard]] const auto getTXID() const { return this->_txid; }
	[[nodiscard]] const auto getIndex() const { return this->_index; }

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech