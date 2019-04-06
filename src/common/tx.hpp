#pragma once

// System includes
#include <vector>

// Project includes
#include "serializable.hpp"
#include "signature.hpp"
#include "state.hpp"
#include "txid.hpp"
#include "utxo.hpp"

class Tx : public Serializable
{
private:
	// Inputs to the transaction
	const std::vector<TXID> _inputs;

	// Outputs of the transaction
	const std::vector<UTXO> _outputs;

	// Digital signatures, one for each input
	const std::vector<Signature> _witnesses;

	// TODO flags?
	// TODO fee/max fee
	// TODO chain ID
	// TODO block height
	// TODO block hash
	// TODO extra data
public:
	// Verifies whether this transaction is valid
	// TODO need to check for double-spends when parallel
	bool verify(const State& state) const;

	std::string serialize() const override;
	Serializable deserialize(std::string s) const override;
};