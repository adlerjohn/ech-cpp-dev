#include "main.hpp"

// System includes
#include <iostream>

// Project includes
#include "foo.hpp"

int main() {
	std::cout << "Hello, World!" << std::endl;

	auto foo = Foo();
	foo.p();

	return 0;
}