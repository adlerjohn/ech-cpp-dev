#include "catch2/catch.hpp"

// Project includes
#include "crypto/keys.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("key derivation (aleth example)", "[crypto][keys]")
{
	auto sk = SecretKey("3ecb44df2159c26e0f995712d4f39b6f6e499b40749b1cf1246c37f9516cb6a4");
	auto pk = PublicKey(sk);

	REQUIRE_THAT("97466f2b32bc3bb76d4741ae51cd1d8578b48d3f1e68da206d47321aec267ce78549b514e4453d74ef11b0cd5e4e4c364effddac8b51bcfc8de80682f952896f", Equals(pk.toHex()));
}


TEST_CASE("key sign", "[crypto][keys]")
{
	auto sk = SecretKey("3ecb44df2159c26e0f995712d4f39b6f6e499b40749b1cf1246c37f9516cb6a4");
	auto pk = PublicKey(sk);

	auto msg = std::string("The quick brown fox jumps over the lazy dog.");
	auto signedMessage = std::string("fd9c0f5b84063479f7b6ff1ccf48dd1ba15c79e10224a5c1a47a3e46025c7e4a188a2f6ba4e109d562e536bd6b03caa83dfc4eba5aa03146f1f2f04404f952e31c");

	SECTION("sign message")
	{
		auto sig = sk.sign(msg);
		REQUIRE_THAT(signedMessage, Equals(sig));
	}
	SECTION("sign digest")
	{
		auto digest = Digest(msg);
		auto sig = sk.sign(digest);
		REQUIRE_THAT(signedMessage, Equals(sig));
	}
}
