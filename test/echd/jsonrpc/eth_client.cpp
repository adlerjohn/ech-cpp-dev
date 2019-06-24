#include "catch2/catch.hpp"

// Project includes
#include "echd/jsonrpc/eth_client.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("eth jsonrpc client leading zeroes empty", "[daemon][jsonrpc]")
{
	const auto s = eth::JsonHelper::removeLeadingZeroes(std::string(""));

	REQUIRE(std::string_view("0") == s);
}

TEST_CASE("eth jsonrpc client leading zeroes zero", "[daemon][jsonrpc]")
{
	const auto s = eth::JsonHelper::removeLeadingZeroes(std::string("0"));

	REQUIRE(std::string_view("0") == s);
}

TEST_CASE("eth jsonrpc client leading zeroes padded zero", "[daemon][jsonrpc]")
{
	const auto s = eth::JsonHelper::removeLeadingZeroes(std::string("0000"));

	REQUIRE(std::string_view("0") == s);
}

TEST_CASE("eth jsonrpc client leading zeroes non-zero", "[daemon][jsonrpc]")
{
	const auto s = eth::JsonHelper::removeLeadingZeroes(std::string("10"));

	REQUIRE(std::string_view("10") == s);
}

TEST_CASE("eth jsonrpc client leading zeroes padded non-zero", "[daemon][jsonrpc]")
{
	const auto s = eth::JsonHelper::removeLeadingZeroes(std::string("0010"));

	REQUIRE(std::string_view("10") == s);
}

TEST_CASE("eth jsonrpc client 0x", "[daemon][jsonrpc]")
{
	const auto s = eth::JsonHelper::formatHex(std::string("42"));

	REQUIRE(std::string_view("0x42") == s);
}