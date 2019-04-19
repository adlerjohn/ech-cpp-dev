#include "main.hpp"

// System includes
#include <iostream>

// Project includes
#include "common/utxo.hpp"
#include "signing.hpp"

using namespace ech;

int main()
{
	std::cout << "Signing with libsecp256k1..." << std::endl;
	auto signing = benchmark::Signing();
	signing.setup();
	std::cout << "Signing setup complete..." << std::endl;
	signing.run();
	std::cout << "Complete in " << signing.getDuration() << "ms." << std::endl;

	return 0;
}