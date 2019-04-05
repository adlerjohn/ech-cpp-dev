#pragma once

// System includes
#include <vector>

// Project includes
#include "utxo.hpp"

class State
{
private:
	// The UTXO set: blockchain state
	std::vector<UTXO> _utxoSet;
public:
};