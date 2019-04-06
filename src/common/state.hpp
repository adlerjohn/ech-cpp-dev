#pragma once

// System includes
#include <vector>
#include <map>

// Project includes
#include "txid.hpp"
#include "utxo.hpp"

class State
{
private:
	// The UTXO set: blockchain state
	const std::map<TXID, UTXO> _utxoSet;
public:
	void add(const std::vector<UTXO> utxos) const;
	void remove(const std::vector<UTXO> utxos) const;
};