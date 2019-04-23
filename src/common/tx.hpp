#pragma once

// System includes
#include <vector>

// Project includes
#include "crypto/signature.hpp"
#include "input.hpp"
#include "serializable.hpp"
#include "state.hpp"
#include "txid.hpp"
#include "txo.hpp"
#include "utxo.hpp"

namespace ech
{

/**
 * Unsigned transaction data.
 */
class TXData : public Serializable
{
private:
	// Transaction ID
	const TXID _id;
	// Version of the transaction
	const uint32_t _version;
	// Inputs to the transaction
	const std::vector<Input> _inputs;
	// Outputs of the transaction
	const std::vector<TXO> _outputs;
	// Minimum height this transaction can be included in
	// If 0, then any height is valid
	const uint64_t _heightMin;
	// Maximum height this transaction can be included in
	// If 0, then any height is valid
	const uint64_t _heightMax;
	// If non-0, the height of a recent block that must exist
	const uint64_t _recentBlockHeight;
	// If recentBlockHeight is non-0, the hash of the recent block
	const crypto::Digest _recentBlockHash;

	// TODO flags?
	// Maximum fee the user is willing to pay per byte
	//	const CoinAmount _maxFeePerByte;

	[[nodiscard]] const std::vector<std::byte> serializeData(
		const uint32_t version,
		const std::vector<Input>& inputs,
		const std::vector<TXO>& outputs,
		const uint64_t heightMin,
		const uint64_t heightMax,
		const uint64_t recentBlockHeight,
		const crypto::Digest& recentBlockHash) const;

public:
	TXData(
		const uint32_t version,
		const std::vector<Input>& inputs,
		const std::vector<TXO>& outputs,
		const uint64_t heightMin,
		const uint64_t heightMax,
		const uint64_t recentBlockHeight,
		const crypto::Digest& recentBlockHash);

	[[nodiscard]] const auto getId() const { return this->_id; }
	[[nodiscard]] const auto getVersion() const { return this->_version; }
	[[nodiscard]] const auto& getInputs() const { return this->_inputs; }
	[[nodiscard]] const auto& getOutputs() const { return this->_outputs; }
	[[nodiscard]] const auto getHeightMin() const { return this->_heightMin; }
	[[nodiscard]] const auto getHeightMax() const { return this->_heightMax; }
	[[nodiscard]] const auto getRecentBlockHeight() const { return this->_recentBlockHeight; }
	[[nodiscard]] const auto& getRecentBlockHash() const { return this->_recentBlockHash; }

	// Get the size of this transaction, in bytes
	[[nodiscard]] const size_t getSize() const;

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

/**
 * Signed transaction (transaction data + witnesses).
 */
class TX : public Serializable
{
private:
	// Transaction data
	const TXData _data;
	// Digital signatures. Each input refer to one of these witnesses.
	const std::vector<crypto::Signature> _witnesses;

	[[nodiscard]] const std::vector<std::byte> serializeData(const TXData& data, const std::vector<crypto::Signature>& witnesses) const;

public:
	TX(const TXData& data, const std::vector<crypto::Signature>& witnesses);

	[[nodiscard]] const auto& getData() const { return this->_data; }
	[[nodiscard]] const auto& getWitnesses() const { return this->_witnesses; }

	// Get the size of this transaction, in bytes
	[[nodiscard]] const size_t getSize() const;

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech