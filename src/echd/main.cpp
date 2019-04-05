#include "main.hpp"

// System includes
#include <iostream>

// Library includes
#include <boost/multiprecision/cpp_int.hpp>
#include <crypto++/eccrypto.h>
#include <crypto++/osrng.h>
#include <crypto++/oids.h>

// Project includes
#include "foo.hpp"
#include "common/utxo.hpp"

int main()
{
	using namespace boost::multiprecision;

	std::cout << "Hello, World!" << std::endl;

	auto foo = Foo();
	foo.p();

	auto utxo = UTXO();

	uint256_t long_int = 0;

	return 0;
}