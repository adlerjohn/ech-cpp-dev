#include "catch2/catch.hpp"

// Project includes
#include "echd/state.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("state zero", "[daemon][state]")
{
	const auto outpoint = Outpoint(TXID(), 0);
	const auto owner = crypto::Address("0000000000000000000000000000000000000000");
	const auto amount = 0;
	const auto color = Color();
	const auto height = 0;

	const auto utxo = UTXO(outpoint, owner, amount, color, height);

	auto state = State();
	REQUIRE(0u == state.size());

	state.add({utxo});
	REQUIRE(1u == state.size());

	state.remove({utxo.getId()});
	REQUIRE(0u == state.size());
}