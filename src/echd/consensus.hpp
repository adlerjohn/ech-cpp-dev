#pragma once

// Project includes
#include "common/block.hpp"
#include "state.hpp"
#include "rewind.hpp"

namespace ech
{

class Consensus
{
private:
	// Blockchain state at the head
	State _state;
	// Data needed to rewind from the head in case of a re-organization
	// TODO implement rewinds
	std::deque<Rewind> _rewinds;

	// TODO keep track of a tree of known block headers

public:
	const bool isBlockValid(const Block& block) const;

	/**
	 * Appends block to the head of the chain.
	 * @param block Block to append.
	 */
	const void appendBlock(const Block& block);

	// TODO fork choice, with block scoring

	// TODO allow executing blocks without verifying signatures if they've already been verified, for faster sync
};

} // namespace ech