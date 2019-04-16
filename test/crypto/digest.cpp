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

TEST_CASE("digest testing", "[crypto][digest]")
{
	auto dig = Digest(std::string("testing"));
	REQUIRE_THAT("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02", Equals(dig.toHex()));
}

TEST_CASE("digest hello", "[crypto][digest]")
{
	auto dig = Digest(std::string("hello"));
	REQUIRE_THAT("1c8aff950685c2ed4bc3174f3472287b56d9517b9c948127319a09a7a36deac8", Equals(dig.toHex()));
}