#include "consensus.hpp"

using namespace ech;

const std::optional<Transition> Consensus::getBlockTransition(const ech::Block& block, const bool assumeValid) const
{
	std::vector<UTXO> additions, removals;

	const auto& header = block.getHeader();

	const auto realHeader = Block(header.getVersion(), header.getPreviousBlockHash(), block.getDeposits(), block.getLeaves(), header.getHeight()).getHeader();

	// TODO check height
	// TODO check prev

	// Check: roots of deposits match
	if (header.getDepositsRoot() != realHeader.getDepositsRoot()) {
		return {};
	}

	// Check: roots of leaves match
	if (header.getTransactionsRoot() != realHeader.getTransactionsRoot()) {
		return {};
	}

	// Add each deposit to the state transition
	for (const auto& deposit : block.getDeposits()) {
		const auto outpoint = Outpoint(deposit.getSource(), 0u);
		const auto utxo = UTXO(outpoint, deposit.getOwner(), deposit.getAmount(), deposit.getColor(), _height + 1);
		// TODO optimize this as emplace_back?
		additions.push_back(utxo);
	}
	// TODO allow deposits to be spent in same transaction

	// Validate each transaction
	for (const auto& tx : block.getLeaves()) {
		const auto& txData = tx.getData();
		const auto& inputs = txData.getInputs();
		const auto& outputs = txData.getOutputs();
		const auto& witnesses = tx.getWitnesses();

		// Check: each input has a witness
		// TODO allow signature batching
		if (!assumeValid && inputs.size() != witnesses.size()) {
			return {};
		}

		// For each input
		for (size_t i = 0; i < inputs.size(); i++) {
			const auto& input = inputs.at(i);
			const auto& outpoint = input.getOutpoint();
			const auto utxoid = UTXOID(outpoint);

			// Check: input exists in the state
			// TODO don't do two lookups
			if (!_state.exists(utxoid)) {
				return {};
			}

			// Check: valid signature
			const auto& utxo = _state.find(utxoid);
			if (!assumeValid) {
				const auto& owner = utxo.getOwner();
				const auto& witness = witnesses.at(i);

				try {
					if (!witness.verify(utxoid, owner)) {
						return {};
					}
				} catch (const std::exception& e) {
					return {};
				}
			}

			// Check: input is not double-spending
			if (std::find_if(removals.begin(), removals.end(), [utxoid](const UTXO& u) -> bool { return u.getId() == utxoid; }) != removals.end()) {
				return {};
			}

			// State transition removes input
			removals.push_back(utxo);
		}

		// Add each output to the state transition
		for (const auto& output : outputs) {
			const auto outpoint = Outpoint(txData.getId(), output.getIndex());
			const auto utxo = UTXO(outpoint, output.getRecipient(), output.getAmount(), output.getColor(), _height + 1);
			additions.push_back(utxo);
		}
	}

	// TODO multi-thread this!
	// TODO enforce canonical transaction ordering

	return Transition(additions, removals);
}

const void Consensus::appendBlock(const ech::Block& block, const Transition& transition)
{
	// TODO also keep track of block headers
	_state.add(transition.getAdditions());
	_state.remove(transition.getRemovals());

	_height++;
}