#pragma once

// System includes
#include <vector>

// Project includes
#include "crypto/signature.hpp"
#include "serializable.hpp"
#include "state.hpp"
#include "txid.hpp"
#include "txo.hpp"
#include "utxo.hpp"

namespace ech
{

class TX : public Serializable
{
private:
	// Transaction ID
	const TXID _id;
	// Inputs to the transaction
	const std::vector<UTXOID> _inputs;
	// Outputs of the transaction
	const std::vector<TXO> _outputs;
	// Digital signatures, one for each input
	const std::vector<crypto::Signature> _witnesses;
	// Minimum height this transaction can be included in
	// If 0, then any height is valid
	const uint64_t _heightMin;
	// Maximum height this transaction can be included in
	// If 0, then any height is valid
	const uint64_t _heightMax;
	// If non-0, the height of a recent block that must exist
	const uint64_t _recentBlockHeight;
	// If recentBlockHeight is non-0, the hash of the recent block
	const uint64_t _recentBlockHash;
	// Replay attack protection
	const uint8_t _chainID;

	// TODO flags?
	// TODO fee/max fee

	[[nodiscard]] const std::vector<std::byte> serializeData(
		const std::vector<UTXOID>& inputs,
		const std::vector<TXO>& outputs) const;

public:
	TX(
		const std::vector<UTXOID>& inputs,
		const std::vector<TXO>& outputs,
		const std::vector<crypto::Signature>& witnesses);

	[[nodiscard]] const auto getId() const { return this->_id; }
	[[nodiscard]] const auto& getInputs() const { return this->_inputs; }
	[[nodiscard]] const auto& getOutputs() const { return this->_outputs; }
	[[nodiscard]] const auto& getWitnesses() const { return this->_witnesses; }
	[[nodiscard]] const auto getHeightMin() const { return this->_heightMin; }
	[[nodiscard]] const auto getHeightMax() const { return this->_heightMax; }
	[[nodiscard]] const auto getRecentBlockHeight() const { return this->_recentBlockHeight; }
	[[nodiscard]] const auto getRecentBlockHash() const { return this->_recentBlockHash; }
	[[nodiscard]] const auto getChainID() const { return this->_chainID; }

	// Get the size of this transaction, in bytes
	[[nodiscard]] const size_t getSize() const;

	// Verifies whether this transaction is valid
	// TODO need to check for double-spends when parallel
	[[nodiscard]] const bool verify(const State& state) const;

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech