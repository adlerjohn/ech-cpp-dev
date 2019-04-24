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
	const auto depositsRoot = crypto::Digest();
	const auto transactionsRoot = crypto::Digest();
	const auto height = 0;

	const auto header = BlockHeader(version, prev, depositsRoot, transactionsRoot, height);

	REQUIRE_THAT("4131b417ff595024f24662aa4eabf1e322f9b49738abb52d4660e96c46f83679", Equals(header.getId().toHex()));

	const auto golden = std::string(
		"00000001"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563"
		"0000000000000000"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563");
	REQUIRE_THAT(golden, Equals(header.toHex()));

	const auto serialized = header.serialize();
	auto q = std::deque<std::byte>(serialized.begin(), serialized.end());
	const auto deserialized = BlockHeader::deserialize(q);
	REQUIRE_THAT(golden, Equals(deserialized.toHex()));
}

TEST_CASE("block header random", "[common][block_header]")
{
	const auto version = 1;
	const auto prev = crypto::Digest();
	const auto depositsRoot = crypto::Digest("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02", true);
	const auto transactionsRoot = crypto::Digest("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02", true);
	const auto height = 42;

	const auto header = BlockHeader(version, prev, depositsRoot, transactionsRoot, height);

	REQUIRE_THAT("ee06534cb316cf31cc825665bf1b55c225dafbe4971f15ba063d9f5ab26ff87d", Equals(header.getId().toHex()));

	const auto golden = std::string(
		"00000001"
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563"
		"000000000000002a"
		"5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02"
		"5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02");
	REQUIRE_THAT(golden, Equals(header.toHex()));

	const auto serialized = header.serialize();
	auto q = std::deque<std::byte>(serialized.begin(), serialized.end());
	const auto deserialized = BlockHeader::deserialize(q);
	REQUIRE_THAT(golden, Equals(deserialized.toHex()));
}

TEST_CASE("block header deserialize short", "[common][block_header]")
{
	auto emtpy = std::deque<std::byte>{};

	REQUIRE_THROWS_AS(BlockHeader::deserialize(emtpy), std::runtime_error);
}