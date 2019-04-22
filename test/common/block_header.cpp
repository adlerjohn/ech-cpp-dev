#include "catch2/catch.hpp"

// Project includes
#include "common/block_header.hpp"
#include "crypto/digest.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("block header empty", "[common][block_header]")
{
	const auto root = crypto::Digest();
	const auto height = 0;

	const auto header = BlockHeader(root, height);

	const auto golden = std::string(
		"520382ef0fa0cf942be88412810103ab3ff49269b6e0d51c675ce400aeb3e5d7"
		"0000000000000000"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563");
	REQUIRE_THAT(golden, Equals(header.toHex()));
}

TEST_CASE("block header random", "[common][block_header]")
{
	const auto root = crypto::Digest("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563", true);
	const auto height = 42;

	const auto header = BlockHeader(root, height);

	const auto golden = std::string(
		"fc656f5c9dc85d9a1347ed82384747604f356ae4ed1d97dc0a619ef7a505c550"
		"000000000000002a"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563");
	REQUIRE_THAT(golden, Equals(header.toHex()));
}