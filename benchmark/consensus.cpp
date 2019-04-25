#include "consensus.hpp"

// Project includes
#include "echd/consensus.hpp"

using namespace ech::benchmark;

void ConsensusBenchmark::setup()
{
}

void ConsensusBenchmark::run()
{
	this->before();

	for (auto& block : this->_data) {
		const auto result = _consensus.getBlockTransition(block);
		if (result) {
			this->_passed++;
			_consensus.appendBlock(block, result.value());
		}
	}

	this->after();
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