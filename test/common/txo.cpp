#include "catch2/catch.hpp"

// Project includes
#include "common/txo.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("txo zero", "[common][txo]")
{
	const auto index = 0;
	const auto recipient = crypto::Address("0000000000000000000000000000000000000000");
	const auto amount = CoinAmount(0);
	const auto color = Color();

	const auto txo = TXO(index, recipient, amount, color);

	const auto golden = std::string(
		"00000000"
		"0000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000"
		"00");
	REQUIRE_THAT(golden, Equals(txo.toHex()));
}

TEST_CASE("txo random", "[common][txo]")
{
	const auto index = 1;
	const auto recipient = crypto::Address("deadbeefdeadbeefdeadbeefdeadbeefdeadbeef");
	const auto amount = CoinAmount(42);
	const auto address = crypto::Address("8a40bfaa73256b60764c1bf40675a99083efb075");
	const auto color = Color(address);

	const auto txo = TXO(index, recipient, amount, color);

	const auto golden = std::string(
		"00000001"
		"deadbeefdeadbeefdeadbeefdeadbeefdeadbeef"
		"000000000000000000000000000000000000000000000000000000000000002a"
		"018a40bfaa73256b60764c1bf40675a99083efb075");
	REQUIRE_THAT(golden, Equals(txo.toHex()));
}