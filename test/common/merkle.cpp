#include "catch2/catch.hpp"

// Project includes
#include "common/merkle.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("Merkle tree empty", "[common][merkle]")
{
	const auto root = MerkleTree(std::vector<crypto::Digest>());

	REQUIRE_THAT("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563", Equals(root.getRoot().toHex()));
}

TEST_CASE("Merkle tree two empty elements", "[common][merkle]")
{
	const auto e1 = crypto::Digest();
	const auto e2 = crypto::Digest();

	const auto root = MerkleTree(std::vector<crypto::Digest>{e1, e2});

	REQUIRE_THAT("633dc4d7da7256660a892f8f1604a44b5432649cc8ec5cb3ced4c4e6ac94dd1d", Equals(root.getRoot().toHex()));
}