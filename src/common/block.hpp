#pragma once

// System includes
#include <vector>

// Project includes
#include "block_header.hpp"
#include "tx.hpp"

class Block
{
private:
	BlockHeader _header;

	// TODO also add interstitial state commitments (change to hashable?)
	std::vector<Tx> _leaves;
public:
};