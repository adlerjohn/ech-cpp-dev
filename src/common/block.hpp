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
	const std::vector<TX> _leaves;

	static const std::vector<crypto::Digest> toLeafHashes(const std::vector<TX>& leaves);

public:
	Block(const std::vector<TX>& leaves, const uint64_t height);

	[[nodiscard]] const auto& getHeader() const { return this->_header; }
	[[nodiscard]] const auto& getLeaves() const { return this->_leaves; }

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech