#include "catch2/catch.hpp"

// Project includes
#include "common/utxo.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("UTXO zero", "[common][utxo]")
{
	const auto address = crypto::Address("0000000000000000000000000000000000000000");
	const auto amount = 0;
	const auto color = Color();

	const auto utxo = UTXO(address, amount, color);

	REQUIRE_THAT("4d8a735acc38ab7f01310ca8e6026ed9f86de88141cd83996db741df5291fc0d", Equals(utxo.getId().toHex()));
}