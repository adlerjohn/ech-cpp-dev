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
	static constexpr uint64_t _blockTxCount = 1000u;
	std::atomic<uint64_t> _passed{0};
	std::vector<Block> _data;
	Consensus _consensus;

public:
	void setup() override;

	void run() override;

	[[nodiscard]] static constexpr auto count() { return _count; }

	void reset() { _passed = 0u; }
};

} // namespace ech::benchmark