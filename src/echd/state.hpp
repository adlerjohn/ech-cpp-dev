#pragma once

// System includes
#include <vector>
#include <map>

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
};

} // namespace ech