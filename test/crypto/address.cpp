#include "catch2/catch.hpp"

// Project includes
#include "crypto/address.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("address zero", "[crypto][addr]")
{
	auto addr = Address(std::string(64*2, '0'));
	REQUIRE_THAT("a1adff1f00dbc095c059f50a397af422de9bcdd3", Equals(addr.toHex()));
}

TEST_CASE("from public key", "[crypto][addr]")
{
	auto addr = Address("689268c0ff57a20cd299fa60d3fb374862aff565b20b5f1767906a99e6e09f3ff04ca2b2a5cd22f62941db103c0356df1a8ed20ce322cab2483db67685afd124");
	REQUIRE_THAT("26d1ec50b4e62c1d1a40d16e7cacc6a6580757d5", Equals(addr.toHex()));
}