#pragma once

// System includes
#include <thread>
#include <vector>

// Project includes
#include "bench.hpp"
#include "echd/consensus.hpp"

namespace ech::benchmark
{

class ConsensusBenchmark : public Benchmark
{
private:
	static constexpr uint64_t _count = 1000u;
	static constexpr uint64_t _blockTxCount = 100u;
	static constexpr uint64_t _addressCount = 1000u;

	std::atomic<uint64_t> _passed{0};
	std::vector<Block> _data;
	uint64_t _transactionsCount = 0;
	std::vector<crypto::SecretKey> _secretKeys;
	std::vector<crypto::Address> _addresses;
	Consensus _consensus;

public:
	void setup() override;

	void run() override;

	[[nodiscard]] static constexpr auto count() { return _count; }
	[[nodiscard]] const auto countTransactions() const { return this->_transactionsCount; }

	void reset() { _passed = 0u; }
};

} // namespace ech::benchmark