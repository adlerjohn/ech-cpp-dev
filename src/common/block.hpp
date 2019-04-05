#pragma once

// System includes
#include <vector>

// Project includes
#include "block_header.hpp"
#include "tx.hpp"

class Block
{
private:
	BlockHeader header;

	// TODO also add interstitial state commitments (change to hashable?)
	std::vector<Tx> leaves;
public:
};