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
	// TODO change this to a sorted vector + smart pointers w/binary search
	// The UTXO set: blockchain state
	std::map<UTXOID, UTXO> _utxoSet;

public:
	[[nodiscard]] static const State deserialize(std::deque<std::byte>& serial);

	void add(const std::vector<UTXO>& utxos);

	void remove(const std::vector<UTXO>& utxos);

	[[nodiscard]] const bool exists(const UTXOID& utxoid) const;
	[[nodiscard]] const UTXO& find(const UTXOID& utxoid) const;

	[[nodiscard]] const auto size() const { return this->_utxoSet.size(); }

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech