#include "catch2/catch.hpp"

// Project includes
#include "crypto/keys.hpp"
#include "crypto/signature.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("key derivation (aleth example)", "[crypto][keys]")
{
	auto secretKey = SecretKey("3ecb44df2159c26e0f995712d4f39b6f6e499b40749b1cf1246c37f9516cb6a4");
	REQUIRE_THAT("3ecb44df2159c26e0f995712d4f39b6f6e499b40749b1cf1246c37f9516cb6a4", Equals(secretKey.toHex()));

	auto publicKey = PublicKey(secretKey);
	REQUIRE_THAT("97466f2b32bc3bb76d4741ae51cd1d8578b48d3f1e68da206d47321aec267ce78549b514e4453d74ef11b0cd5e4e4c364effddac8b51bcfc8de80682f952896f", Equals(publicKey.toHex()));
}