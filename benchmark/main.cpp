#include "main.hpp"

// System includes
#include <iostream>

// Project includes
#include "common/utxo.hpp"
#include "signing.hpp"

using namespace ech;

int main()
{
	std::cout << "Setting up " << benchmark::Signing::count() << " tests with libsecp256k1..." << std::endl;
	auto signing = benchmark::Signing();
	signing.setup();
	std::cout << "Signing setup complete..." << std::endl;
	std::cout << std::endl;

	std::cout << "Running single-threaded benchmarking..." << std::endl;
	signing.run();
	std::cout << "Complete in " << signing.getDuration() << "ms." << std::endl;
	signing.reset();
	std::cout << std::endl;

	constexpr auto threadCount = 4u;
	std::cout << "Running multi-threaded benchmarking with " << threadCount << " threads..." << std::endl;
	signing.run(threadCount);
	std::cout << "Complete in " << signing.getDuration() << "ms." << std::endl;
	signing.reset();
	std::cout << std::endl;

	return 0;
}