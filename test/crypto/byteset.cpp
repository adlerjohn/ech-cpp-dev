#include "catch2/catch.hpp"

// Project includes
#include "crypto/byteset.hpp"

using namespace ech::crypto;

TEST_CASE("byteset length", "[byteset]")
{
	auto bs = byteset<1u>();
	REQUIRE(std::string("00").compare(bs.toHex()) == 0);
}

TEST_CASE("byteset length, incorrect comparison", "[byteset][!shouldfail]")
{
	auto bs = byteset<1u>();
	REQUIRE(std::string("0").compare(bs.toHex()) == 0);
}