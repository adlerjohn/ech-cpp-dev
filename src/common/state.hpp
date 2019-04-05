#pragma once

// System includes
#include <vector>

// Project includes
#include "utxo.hpp"

class State
{
private:
	// The UTXO set: blockchain state
	const std::vector<UTXO> _utxoSet;
public:
};