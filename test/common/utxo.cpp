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

TEST_CASE("UTXO random", "[common][utxo]")
{
	const auto address = crypto::Address("8a40bfaa73256b60764c1bf40675a99083efb075");
	const auto amount = 42;
	const auto color = Color(crypto::Address("deadbeefdeadbeefdeadbeefdeadbeefdeadbeef"));

	const auto utxo = UTXO(address, amount, color);

	REQUIRE_THAT("34d12d2dcfef9ef209739bfd20e6073a64d77d588bff48a97fd30bb215b1410a", Equals(utxo.getId().toHex()));
}