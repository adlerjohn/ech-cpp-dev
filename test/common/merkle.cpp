#include "catch2/catch.hpp"

// Project includes
#include "common/merkle.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("Merkle tree empty", "[common][merkle]")
{
	const auto zero = std::vector<std::byte>(crypto::Digest::size(), std::byte(0x00));

	const auto root = MerkleTree(std::vector<crypto::Digest>());

	REQUIRE_THAT("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563", Equals(root.getRoot().toHex()));
}

TEST_CASE("Merkle tree two empty elements", "[common][merkle]")
{
	const auto zero = std::vector<std::byte>(crypto::Digest::size(), std::byte(0x00));
	const auto e1 = crypto::Digest(zero);
	const auto e2 = crypto::Digest(zero);

	const auto root = MerkleTree(std::vector<crypto::Digest>{e1, e2});

	REQUIRE_THAT("ad3228b676f7d3cd4284a5443f17f1962b36e491b30a40b2405849e597ba5fb5", Equals(root.getRoot().toHex()));
}