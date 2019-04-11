#pragma once

// System includes
#include <vector>

// Project includes
#include "block_header.hpp"
#include "tx.hpp"

namespace ech
{

class Block
{
private:
	const BlockHeader _header;

	// TODO also add interstitial state commitments (change to hashable?)
	const std::vector<Tx> _leaves;
public:
};

} // namespace ech