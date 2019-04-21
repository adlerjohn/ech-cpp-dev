#include "catch2/catch.hpp"

// Project includes
#include "crypto/digest.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("digest empty", "[crypto][digest]")
{
	const auto dig = Digest(std::string());
	REQUIRE_THAT("c5d2460186f7233c927e7db2dcc703c0e500b653ca82273b7bfad8045d85a470", Equals(dig.toHex()));
}

TEST_CASE("digest string zeroes", "[crypto][digest]")
{
	const auto dig = Digest(std::string(64*2, '0'));
	REQUIRE_THAT("a1adff1f00dbc095c059f50a397af422de9bcdd342c417d304c957b5e7ceb908", Equals(dig.toHex()));
}

TEST_CASE("digest testing", "[crypto][digest]")
{
	const auto dig = Digest(std::string("testing"));
	REQUIRE_THAT("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02", Equals(dig.toHex()));
}

TEST_CASE("digest hello", "[crypto][digest]")
{
	const auto dig = Digest(std::string("hello"));
	REQUIRE_THAT("1c8aff950685c2ed4bc3174f3472287b56d9517b9c948127319a09a7a36deac8", Equals(dig.toHex()));
}

TEST_CASE("digest zero", "[crypto][digest]")
{
	const auto zero = std::vector<std::byte>(Digest::size(), std::byte(0x00));
	const auto digest = Digest(zero);

	REQUIRE_THAT("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563", Equals(digest.toHex()));
}

TEST_CASE("digest concat zeroes", "[crypto][digest]")
{
	const auto zero = std::vector<std::byte>(Digest::size(), std::byte(0x00));
	const auto dig1 = Digest(zero);
	const auto dig2 = Digest(zero);

	const auto dig12 = dig1 + dig2;

	REQUIRE_THAT("ad3228b676f7d3cd4284a5443f17f1962b36e491b30a40b2405849e597ba5fb5", Equals(dig12.toHex()));
}

TEST_CASE("digest concat words", "[crypto][digest]")
{
	const auto dig1 = Digest(std::string("hello"));
	const auto dig2 = Digest(std::string("testing"));

	const auto dig12 = dig1 + dig2;

	REQUIRE_THAT("8087ef925637b0533aa54145b2184d1ee6c88a0abc65d61e01996c6764cacf49", Equals(dig12.toHex()));
}