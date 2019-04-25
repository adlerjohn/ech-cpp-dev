#pragma once

// Project includes
#include "common/block.hpp"
#include "state.hpp"
#include "transition.hpp"

namespace ech
{

class Consensus
{
private:
	// Blockchain state at the head
	State _state;
	// Data needed to rewind from the head in case of a re-organization
	// TODO implement rewinding transitions
	std::deque<Transition> _transitions;
	// Height of the current head
	uint64_t _height = 0;

	// TODO keep track of a tree of known block headers

public:
	/**
	 * Validates a block and gets its state transition if valid.
	 * @param block Block the validate.
	 * @return Optional state transition, on success.
	 */
	const std::optional<Transition> getBlockTransition(const Block& block, const bool assumeValid = false) const;

	/**
	 * Appends block to the head of the chain.
	 * @param block Block to append.
	 * @param transition State transition of the block, to apply.
	 */
	const void appendBlock(const Block& block, const Transition& transition);

	// TODO fork choice, with block scoring

	// TODO allow executing blocks without verifying signatures if they've already been verified, for faster sync

	[[nodiscard]] const auto getState() const { return this->_state; }
};

} // namespace ech