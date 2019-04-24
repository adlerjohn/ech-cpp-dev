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

	REQUIRE_THAT("3e327054f60b9c38a1c3fafb23d155d0f971a83a616685eb79c73127b3dfbcc5", Equals(deposit.getSource().toHex()));

	const auto golden = std::string(
		"0000000000000000000000000000000000000000" // owner
		"0000000000000000000000000000000000000000000000000000000000000000" // amount
		"00" // color
		"0000000000000000" // height
		"0000000000000000" // nonce
	);
	REQUIRE_THAT(golden, Equals(deposit.toHex()));

	const auto serialized = deposit.serialize();
	auto q = std::deque<std::byte>(serialized.begin(), serialized.end());
	const auto deserialized = Deposit::deserialize(q);
	REQUIRE_THAT(golden, Equals(deserialized.toHex()));
}

TEST_CASE("deposit deserialize short", "[common][deposit]")
{
	auto emtpy = std::deque<std::byte>{};

	REQUIRE_THROWS_AS(Deposit::deserialize(emtpy), std::runtime_error);
}