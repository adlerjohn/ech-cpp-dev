#pragma once

// System includes
#include <vector>

// Project includes
#include "signature.hpp"
#include "utxo.hpp"

class Tx
{
private:
	// Inputs to the transaction
	const std::vector<UTXO> _inputs;

	// Outputs of the transaction
	const std::vector<UTXO> _outputs;

	// Digital signature, one for each input
	const std::vector<Signature> _sig;
public:
};