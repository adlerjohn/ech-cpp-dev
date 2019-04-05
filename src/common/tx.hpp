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
	std::vector<UTXO> _inputs;

	// Outputs of the transaction
	std::vector<UTXO> _outputs;

	// Digital signature, one for each input
	std::vector<Signature> _sig;
public:
};