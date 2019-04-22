#include "catch2/catch.hpp"

// Project includes
#include "common/utxo.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("UTXO zero", "[common][utxo]")
{
	const auto outpoint = Outpoint(TXID(), 0);
	const auto id = UTXOID(outpoint);
	const auto owner = crypto::Address("0000000000000000000000000000000000000000");
	const auto amount = 0;
	const auto color = Color();
	const auto height = 0;

	const auto utxo = UTXO(id, owner, amount, color, height);

	REQUIRE_THAT(id.toHex(), Equals(utxo.getId().toHex()));
	REQUIRE_THAT("0000000000000000000000000000000000000000", Equals(utxo.getOwner().toHex()));
	REQUIRE(0 == utxo.getAmount());
	REQUIRE_FALSE(utxo.isColored());
	REQUIRE(0 == utxo.getHeight());
}

TEST_CASE("UTXO random", "[common][utxo]")
{
	const auto outpoint = Outpoint(TXID(), 0);
	const auto id = UTXOID(outpoint);
	const auto owner = crypto::Address("8a40bfaa73256b60764c1bf40675a99083efb075");
	const auto amount = 42;
	const auto color = Color(crypto::Address("deadbeefdeadbeefdeadbeefdeadbeefdeadbeef"));
	const auto height = 7;

	const auto utxo = UTXO(id, owner, amount, color, height);

	REQUIRE_THAT(id.toHex(), Equals(utxo.getId().toHex()));
	REQUIRE_THAT("8a40bfaa73256b60764c1bf40675a99083efb075", Equals(utxo.getOwner().toHex()));
	REQUIRE(42 == utxo.getAmount());
	REQUIRE(utxo.isColored());
	REQUIRE_THAT("deadbeefdeadbeefdeadbeefdeadbeefdeadbeef", Equals(utxo.getColor().getColor().toHex()));
	REQUIRE(7 == utxo.getHeight());
}