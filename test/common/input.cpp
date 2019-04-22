#include "catch2/catch.hpp"

// Project includes
#include "common/input.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("input zero", "[common][input]")
{
	const auto outpoint = Outpoint(TXID(), 0);
	const auto input = Input(outpoint, 0);

	REQUIRE_THAT("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e5630000000000000000", Equals(input.toHex()));
}

TEST_CASE("input random", "[common][input]")
{
	const auto digest = crypto::Digest("testing");
	const auto outpoint = Outpoint(TXID(digest), 42);
	const auto input = Input(outpoint, 7);

	REQUIRE_THAT("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b020000002a00000007", Equals(input.toHex()));
}