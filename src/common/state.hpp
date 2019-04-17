#pragma once

// System includes
#include <vector>
#include <map>

// Project includes
#include "utxo.hpp"

namespace ech
{

class State
{
private:
	// The UTXO set: blockchain state
	const std::map<UTXOID, UTXO> _utxoSet;
public:
	void add(const std::vector<UTXO>& utxos) const;

	void remove(const std::vector<UTXO>& utxos) const;
};

} // namespace ech