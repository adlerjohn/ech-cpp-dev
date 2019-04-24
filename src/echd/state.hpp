#pragma once

// System includes
#include <map>
#include <vector>

// Project includes
#include "common/utxo.hpp"

namespace ech
{

class State
{
private:
	// The UTXO set: blockchain state
	std::map<UTXOID, UTXO> _utxoSet;

public:
	void add(const std::vector<UTXO>& utxos);

	void remove(const std::vector<UTXO>& utxos);

	[[nodiscard]] const auto size() const { return this->_utxoSet.size(); }
};

} // namespace ech