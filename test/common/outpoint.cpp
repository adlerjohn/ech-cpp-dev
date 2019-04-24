#include "catch2/catch.hpp"

// Project includes
#include "common/outpoint.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("outpoint zero", "[common][outpoint]")
{
	const auto outpoint = Outpoint(TXID(), 0);

	REQUIRE_THAT("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e56300000000", Equals(outpoint.toHex()));
}

TEST_CASE("outpoint testing 0", "[common][outpoint]")
{
	const auto digest = crypto::Digest("testing");
	const auto outpoint = Outpoint(TXID(digest), 0u);

	REQUIRE_THAT("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b0200000000", Equals(outpoint.toHex()));

	auto serialized = outpoint.serialize();
	const auto deserialized = Outpoint::deserialize(serialized);
	REQUIRE_THAT(outpoint.toHex(), Equals(deserialized.toHex()));
}

TEST_CASE("outpoint testing 42", "[common][outpoint]")
{
	const auto digest = crypto::Digest("testing");
	const auto outpoint = Outpoint(TXID(digest), 42u);

	REQUIRE_THAT("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b020000002a", Equals(outpoint.toHex()));

	auto serialized = outpoint.serialize();
	const auto deserialized = Outpoint::deserialize(serialized);
	REQUIRE_THAT(outpoint.toHex(), Equals(deserialized.toHex()));
}

TEST_CASE("outpoint deserialize short", "[common][outpoint]")
{
	auto bad1 = std::vector<std::byte>{};

	REQUIRE_THROWS_AS(Outpoint::deserialize(bad1), std::runtime_error);
}