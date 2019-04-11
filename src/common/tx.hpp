#pragma once

// System includes
#include <vector>

// Project includes
#include "crypto/signature.hpp"
#include "serializable.hpp"
#include "state.hpp"
#include "utxo.hpp"

namespace ech
{

class Tx : public Serializable
{
private:
	// Inputs to the transaction
	const std::vector<UTXOID> _inputs;

	// Outputs of the transaction
	const std::vector<UTXO> _outputs;

	// Digital signatures, one for each input
	const std::vector<crypto::Signature> _witnesses;

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

	Serializable deserialize(const std::string& s) const override;
};

} // namespace ech