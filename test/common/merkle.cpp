#include "catch2/catch.hpp"

// Project includes
#include "common/merkle.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("Merkle tree empty", "[common][merkle]")
{
	const auto digest = crypto::Digest("0000000000000000000000000000000000000000000000000000000000000000");
	const auto root = MerkleTree(std::vector<crypto::Digest>());

	REQUIRE_THAT(digest.toHex(), Equals(root.getRoot().toHex()));
}