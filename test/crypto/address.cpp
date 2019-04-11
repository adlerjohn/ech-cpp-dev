#include "catch2/catch.hpp"

// Project includes
#include "crypto/address.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("address zero", "[crypto][addr]")
{
	auto addr = Address(std::string(64*2, '0'));
	REQUIRE_THAT("a1adff1f00dbc095c059f50a397af422de9bcdd3", Equals(addr.getAddress().toHex()));
}