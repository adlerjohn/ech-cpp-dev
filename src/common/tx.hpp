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
	std::vector<UTXO> inputs;

	// Outputs of the transaction
	std::vector<UTXO> outputs;

	// Digital signature, one for each input
	std::vector<Signature> sig;
public:
};