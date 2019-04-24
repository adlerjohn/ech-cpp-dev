#pragma once

// System includes
#include <map>
#include <vector>

// Project includes
#include "common/utxo.hpp"

namespace ech
{

class State : public Serializable
{
private:
	// The UTXO set: blockchain state
	std::map<UTXOID, UTXO> _utxoSet;

public:
	[[nodiscard]] static const State deserialize(std::deque<std::byte>& serial);

	void add(const std::vector<UTXO>& utxos);

	void remove(const std::vector<UTXO>& utxos);

	[[nodiscard]] const auto size() const { return this->_utxoSet.size(); }

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech