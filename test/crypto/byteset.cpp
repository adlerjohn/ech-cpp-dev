#include "catch2/catch.hpp"

// Project includes
#include "crypto/byteset.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("byteset length", "[crypto][byteset]")
{
	auto bs = byteset<1u>();
	REQUIRE_THAT(std::string("00"), Equals(bs.toHex()));
}

TEST_CASE("byteset length, incorrect comparison", "[crypto][byteset]")
{
	auto bs = byteset<1u>();
	REQUIRE_THAT(std::string("0"), !Equals(bs.toHex()));
}

TEST_CASE("byteset input", "[crypto][byteset]")
{
	auto str = std::string("01234567");
	auto bs = byteset<4u>(str);
	REQUIRE_THAT(str, Equals(bs.toHex()));
}