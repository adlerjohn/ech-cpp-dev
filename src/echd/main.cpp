#include "main.hpp"

// System includes
#include <iostream>

// Project includes
#include "foo.hpp"
#include "utxo.hpp"

int main()
{
	std::cout << "Hello, World!" << std::endl;

	auto foo = Foo();
	foo.p();

	auto utxo = UTXO();
	utxo.p();

	return 0;
}