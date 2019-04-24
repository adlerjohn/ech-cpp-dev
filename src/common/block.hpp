#pragma once

// System includes
#include <vector>

// Project includes
#include "block_header.hpp"
#include "deposit.hpp"
#include "serializable.hpp"
#include "tx.hpp"

namespace ech
{

class Block : public Serializable
{
private:
	const BlockHeader _header;
	const std::vector<Deposit> _deposits;
	// TODO also add interstitial state commitments (change to hashable?)
	const std::vector<TX> _leaves;

	static const std::vector<crypto::Digest> toDepositHashes(const std::vector<Deposit>& deposits);

	static const std::vector<crypto::Digest> toLeafHashes(const std::vector<TX>& leaves);

public:
	Block(const uint32_t version, const crypto::Digest& prev, const std::vector<Deposit>& deposits, const std::vector<TX>& leaves, const uint64_t height);

	[[nodiscard]] static const Block deserialize(std::vector<std::byte>& serial);

	[[nodiscard]] const auto& getHeader() const { return this->_header; }
	[[nodiscard]] const auto& getDeposits() const { return this->_deposits; }
	[[nodiscard]] const auto& getLeaves() const { return this->_leaves; }

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech