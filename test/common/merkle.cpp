#include "catch2/catch.hpp"

// Project includes
#include "common/merkle.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("Merkle tree empty", "[common][merkle]")
{
	const auto zero = std::vector<std::byte>(crypto::Digest::size(), std::byte(0x00));
	const auto digest = crypto::Digest(zero);

	const auto root = MerkleTree(std::vector<crypto::Digest>());

	REQUIRE_THAT(digest.toHex(), Equals(root.getRoot().toHex()));
}

TEST_CASE("Merkle tree two empty elements", "[common][merkle]")
{
	const auto zero = std::vector<std::byte>(crypto::Digest::size(), std::byte(0x00));
	const auto digest = crypto::Digest(zero);
	const auto e1 = crypto::Digest(zero);
	const auto e2 = crypto::Digest(zero);

	const auto root = MerkleTree(std::vector<crypto::Digest>{e1, e2});

	REQUIRE_THAT(digest.toHex(), Equals(root.getRoot().toHex()));
}