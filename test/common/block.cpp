#include "catch2/catch.hpp"

// Project includes
#include "common/block.hpp"
#include "common/merkle.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("block zero", "[common][block]")
{
	const auto leaves = std::vector<TX>{};

	const auto block = Block(leaves, 0);

	const auto golden = std::string(
		"520382ef0fa0cf942be88412810103ab3ff49269b6e0d51c675ce400aeb3e5d70000000000000000290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563"
		"0000000000000000");
	REQUIRE_THAT(golden, Equals(block.toHex()));
}