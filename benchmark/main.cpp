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
	signing.setup();
	std::cout << "Signing setup complete..." << std::endl;

	std::cout << "Running for Crypto++..." << std::endl;
	signing.run(crypto::Signer_CryptoPP());
	std::cout << "Complete in " << signing.getDuration() << "s." << std::endl;

	std::cout << "Running for libsecp256k1..." << std::endl;
	signing.run(crypto::Signer_libsecp256k1());
	std::cout << "Complete in " << signing.getDuration() << "s." << std::endl;

	return 0;
}