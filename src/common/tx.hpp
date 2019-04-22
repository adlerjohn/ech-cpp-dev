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

class Tx : public Serializable
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

	// TODO flags?
	// TODO fee/max fee
	// TODO chain ID
	// TODO block height
	// TODO block hash
	// TODO extra data
public:
	Tx(const std::vector<UTXOID>& inputs, const std::vector<TXO>& outputs, const std::vector<crypto::Signature>& witnesses);

	// Verifies whether this transaction is valid
	// TODO need to check for double-spends when parallel
	[[nodiscard]] const bool verify(const State& state) const;

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech