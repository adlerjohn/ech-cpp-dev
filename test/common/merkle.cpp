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

TEST_CASE("Merkle tree <testing, --->", "[common][merkle]")
{
	const auto e1 = crypto::Digest("testing");

	const auto root = MerkleTree(std::vector<crypto::Digest>{e1});

	REQUIRE_THAT("9da753915966850e99d6f2fca7066ed1b4e59e762e4b08c7254ade7102dfc26e", Equals(root.getRoot().toHex()));
}

TEST_CASE("Merkle tree <testing, hello>", "[common][merkle]")
{
	const auto e1 = crypto::Digest("testing");
	const auto e2 = crypto::Digest("hello");

	const auto root = MerkleTree(std::vector<crypto::Digest>{e1, e2});

	REQUIRE_THAT("7c310f6da60e3cca363a77838448c580a9f11ad9c28bdf39a99922e0c911041e", Equals(root.getRoot().toHex()));
}

TEST_CASE("Merkle tree <zero, zero, testing, hello>", "[common][merkle]")
{
	const auto e1 = crypto::Digest();
	const auto e2 = crypto::Digest();
	const auto e3 = crypto::Digest("testing");
	const auto e4 = crypto::Digest("hello");

	const auto root = MerkleTree(std::vector<crypto::Digest>{e1, e2, e3, e4});

	REQUIRE_THAT("f597a38c14a52fef1f520939a2102c6b97329f1b7d2bb330c7105eb5f8960e9d", Equals(root.getRoot().toHex()));
}