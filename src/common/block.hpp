#pragma once

// System includes
#include <vector>

// Project includes
#include "block_header.hpp"
#include "serializable.hpp"
#include "tx.hpp"

namespace ech
{

class Block : public Serializable
{
private:
	const BlockHeader _header;

	// TODO also add interstitial state commitments (change to hashable?)
	const std::vector<Tx> _leaves;
public:
	std::string serialize() const override;

	Serializable deserialize(const std::string& s) const override;
};

} // namespace ech