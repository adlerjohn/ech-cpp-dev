#include "main.hpp"

// System includes
#include <iostream>

// Project includes
#include "common/utxo.hpp"
#include "signing.hpp"

using namespace ech;

int main()
{
	std::cout << "Signing..." << std::endl;

	auto signing = benchmark::Signing();
	signing.run();

	std::cout << "Complete in " << signing.getDuration() << "s." << std::endl;

	return 0;
}