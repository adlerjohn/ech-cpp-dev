#include "catch2/catch.hpp"

// Project includes
#include "common/utxoid.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("utxoid zero", "[common][utxoid]")
{
	const auto digest = crypto::Digest();
	const auto outpoint = Outpoint(TXID(digest), 0);
	const auto id = UTXOID(outpoint);

	REQUIRE_THAT("462453416484cee1887d8aa607335428cd1896f10e5148a6d1989e116ef9b890", Equals(id.toHex()));
}

TEST_CASE("utxoid random", "[common][utxoid]")
{
	const auto digest = crypto::Digest("testing");
	const auto outpoint = Outpoint(TXID(digest), 42);
	const auto id = UTXOID(outpoint);

	REQUIRE_THAT("60f9d38adbdcf47a0746abc5ee9d0f5685b1bd02d670c5caf2cd6c9878c768ba", Equals(id.toHex()));
}