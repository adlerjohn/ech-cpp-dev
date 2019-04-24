#include "catch2/catch.hpp"

// Project includes
#include "common/color.hpp"
#include "crypto/address.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("color no", "[common][color]")
{
	const auto color = Color();

	REQUIRE_FALSE(color.isColored());
	REQUIRE(1 == color.serialize().size());
	REQUIRE_THAT("00", Equals(color.toHex()));

	auto serialized = color.serialize();
	const auto deserialized = Color::deserialize(serialized);
	REQUIRE_THAT(color.toHex(), Equals(deserialized.toHex()));
}

TEST_CASE("color yes", "[common][color]")
{
	const auto address = crypto::Address("8a40bfaa73256b60764c1bf40675a99083efb075");
	const auto color = Color(address);

	REQUIRE(color.isColored());
	REQUIRE(crypto::Address::size() + 1 == color.serialize().size());
	REQUIRE_THAT("018a40bfaa73256b60764c1bf40675a99083efb075", Equals(color.toHex()));

	auto serialized = color.serialize();
	const auto deserialized = Color::deserialize(serialized);
	REQUIRE_THAT(color.toHex(), Equals(deserialized.toHex()));
}

TEST_CASE("color deserialize incorrect", "[common][color]")
{
	auto bad1 = std::vector<std::byte>{};

	REQUIRE_THROWS_AS(Color::deserialize(bad1), std::runtime_error);

	auto bad2 = std::vector<std::byte>{std::byte(0x01), std::byte(0x00)};

	REQUIRE_THROWS_AS(Color::deserialize(bad2), std::runtime_error);
}