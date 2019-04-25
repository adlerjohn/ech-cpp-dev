#include "consensus.hpp"

// Project includes
#include "echd/consensus.hpp"

using namespace ech::benchmark;

void ConsensusBenchmark::runThread(const size_t begin, const size_t size)
{
}

void ConsensusBenchmark::setup()
{
}

void ConsensusBenchmark::run()
{
}

void ConsensusBenchmark::run(const uint64_t threadCount)
{
}

int main()
{
	std::cout << "Setting up consensus tests for " << ConsensusBenchmark::count() << " blocks..." << std::endl;
	auto consensus = ConsensusBenchmark();
	consensus.setup();
	std::cout << "Consensus setup complete..." << std::endl;
	std::cout << std::endl;

	std::cout << "Running single-threaded benchmarking..." << std::endl;
	consensus.run();
	std::cout << "Complete in " << consensus.getDuration() << "ms." << std::endl;
	consensus.reset();
	std::cout << std::endl;

	return 0;
}