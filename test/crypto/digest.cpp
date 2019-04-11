#include "catch2/catch.hpp"

// Project includes
#include "crypto/digest.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("digest empty", "[crypto][digest]")
{
	auto dig = Digest(std::string());
	REQUIRE_THAT("c5d2460186f7233c927e7db2dcc703c0e500b653ca82273b7bfad8045d85a470", Equals(dig.toHex()));
}

TEST_CASE("digest zero", "[crypto][digest]")
{
	auto dig = Digest(std::string(64*2, '0'));
	REQUIRE_THAT("a1adff1f00dbc095c059f50a397af422de9bcdd342c417d304c957b5e7ceb908", Equals(dig.toHex()));
}