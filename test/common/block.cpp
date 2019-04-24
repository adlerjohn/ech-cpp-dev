#include "catch2/catch.hpp"

// Project includes
#include "common/block.hpp"
#include "common/merkle.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("block zero", "[common][block]")
{
	const auto deposits = std::vector<Deposit>{};
	const auto leaves = std::vector<TX>{};

	const auto version = 1;
	const auto prev = crypto::Digest();
	const auto block = Block(version, prev, deposits, leaves, 0);

	REQUIRE_THAT("4131b417ff595024f24662aa4eabf1e322f9b49738abb52d4660e96c46f83679", Equals(block.getHeader().getId().toHex()));

	const auto golden = std::string(
		"00000001" // version
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563" // prev
		"0000000000000000" // height
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563" // deposits root
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563" // leaves root
		"0000000000000000" // deposits count
		"0000000000000000" // leaves count
	);
	REQUIRE_THAT(golden, Equals(block.toHex()));

	auto serialized = block.serialize();
	const auto deserialized = Block::deserialize(serialized);
	REQUIRE_THAT(golden, Equals(deserialized.toHex()));
}

TEST_CASE("block deserialize short", "[common][block]")
{
	auto emtpy = std::vector<std::byte>{};

	REQUIRE_THROWS_AS(Block::deserialize(emtpy), std::runtime_error);
}