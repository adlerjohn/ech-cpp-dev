#include "catch2/catch.hpp"

// Project includes
#include "common/deposit.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("deposit zero", "[common][deposit]")
{
	const auto owner = crypto::Address("0000000000000000000000000000000000000000");
	const auto amount = 0;
	const auto color = Color();
	const auto height = 0;
	const auto nonce = 0;

	const auto deposit = Deposit(owner, amount, color, height, nonce);

	const auto golden = std::string(
		"3e327054f60b9c38a1c3fafb23d155d0f971a83a616685eb79c73127b3dfbcc5"
		"0000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000"
		"00"
		"0000000000000000"
		"0000000000000000");
	REQUIRE_THAT(golden, Equals(deposit.toHex()));
}