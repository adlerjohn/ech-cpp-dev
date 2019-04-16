#include "catch2/catch.hpp"

// Project includes
#include "crypto/keys.hpp"
#include "crypto/signature.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("key derivation (aleth example)", "[crypto][keys]")
{
	auto secretKey = SecretKey("3ecb44df2159c26e0f995712d4f39b6f6e499b40749b1cf1246c37f9516cb6a4");
	auto publicKey = PublicKey(secretKey);

	REQUIRE_THAT("97466f2b32bc3bb76d4741ae51cd1d8578b48d3f1e68da206d47321aec267ce78549b514e4453d74ef11b0cd5e4e4c364effddac8b51bcfc8de80682f952896f", Equals(publicKey.toHex()));
}

TEST_CASE("key sign", "[crypto][keys]")
{
	auto secretKey = SecretKey("3ecb44df2159c26e0f995712d4f39b6f6e499b40749b1cf1246c37f9516cb6a4");
	auto msg = std::string("The quick brown fox jumps over the lazy dog.");

	SECTION("sign message")
	{
		auto sig = secretKey.sign(msg);
		REQUIRE(Signature::size() * 2 == sig.length());
		REQUIRE_THAT("5385685eef5fe0f2f93fa022002bb00f8b2478b9567618e47463cda72a78dcdb56a7a6bcd0bd79f709f15e0d3d53ba9909d4a3d100e25065bc0b7bd2537f39191c", Equals(sig));
	}
}