#pragma once

// Project includes
#include "outpoint.hpp"

namespace ech
{

class Input : public Serializable
{
private:
	const Outpoint _outpoint;
	// The index of the witness that signs for this outpoint
	const uint32_t _witnessIndex;

public:
	Input(const Outpoint& outpoint, const uint32_t witnessIndex);

	[[nodiscard]] static const Input deserialize(std::deque<std::byte>& serial);

	[[nodiscard]] const auto& getOutpoint() const { return this->_outpoint; }
	[[nodiscard]] const auto getWitnessIndex() const { return this->_witnessIndex; }

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech