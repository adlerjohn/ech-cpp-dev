#include "catch2/catch.hpp"

// Project includes
#include "common/block_header.hpp"
#include "crypto/digest.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("block header empty", "[common][block_header]")
{
	const auto version = 1;
	const auto prev = crypto::Digest();
	const auto root = crypto::Digest();
	const auto height = 0;

	const auto header = BlockHeader(version, prev, root, height);

	const auto golden = std::string(
		"34499c2f4cbdde7afcb0524dc8811dceb653aea9227bb67466805def49d116f3"
		"00000001"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563"
		"0000000000000000"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563");
	REQUIRE_THAT(golden, Equals(header.toHex()));
}

TEST_CASE("block header random", "[common][block_header]")
{
	const auto version = 1;
	const auto prev = crypto::Digest();
	const auto root = crypto::Digest("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02", true);
	const auto height = 42;

	const auto header = BlockHeader(version, prev, root, height);

	const auto golden = std::string(
		"9c2d4d8159e00437dcd5ab4ddbe15ef5ccfbeabce2173e04d10101da5d20120b"
		"00000001"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563"
		"000000000000002a"
		"5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02");
	REQUIRE_THAT(golden, Equals(header.toHex()));
}