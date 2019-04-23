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

	const auto golden = std::string(
		"4131b417ff595024f24662aa4eabf1e322f9b49738abb52d4660e96c46f83679"
		"00000001"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563"
		"0000000000000000"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563"
		"0000000000000000"
		"0000000000000000");
	REQUIRE_THAT(golden, Equals(block.toHex()));
}