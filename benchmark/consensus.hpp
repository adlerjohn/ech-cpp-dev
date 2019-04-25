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
	static constexpr uint64_t _count = 10u;
	static constexpr uint64_t _blockTxCount = 10u;
	static constexpr uint64_t _addressCount = 10u;

	std::atomic<uint64_t> _passed{0};
	std::vector<Block> _data;
	std::vector<crypto::SecretKey> _secretKeys;
	std::vector<crypto::Address> _addresses;
	Consensus _consensus;

public:
	void setup() override;

	void run() override;

	[[nodiscard]] static constexpr auto count() { return _count; }
	[[nodiscard]] static constexpr auto countTransactions() { return _count * _blockTxCount; }

	void reset() { _passed = 0u; }
};

} // namespace ech::benchmark