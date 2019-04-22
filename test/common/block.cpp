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

	REQUIRE_THAT("", Equals(block.toHex()));
}