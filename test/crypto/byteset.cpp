#include "catch2/catch.hpp"

// Project includes
#include "crypto/byteset.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("byteset input numbers", "[crypto][byteset]")
{
	auto str = std::string("01234567");
	auto bs = byteset<4u>(str);
	REQUIRE_THAT(str, Equals(bs.toHex()));
}

TEST_CASE("byteset letters", "[crypto][byteset]")
{
	auto str = std::string("abcdef");
	auto bs = byteset<3u>(str);
	REQUIRE_THAT(str, Equals(bs.toHex()));
}

TEST_CASE("byteset incorrect size", "[crypto][byteset]")
{
	auto str = std::string("01234");
	REQUIRE_THROWS(byteset<1u>(str));
}

TEST_CASE("byteset zero address", "[crypto][byteset]")
{
	auto str = std::string("a1adff1f00dbc095c059f50a397af422de9bcdd3");
	auto bs = byteset<20u>(str);
	REQUIRE_THAT(str, Equals(bs.toHex()));
}

TEST_CASE("byteset invalid string", "[crypto][byteset]")
{
	auto str = std::string("0ww0");
	REQUIRE_THROWS(byteset<2u>(str));
}