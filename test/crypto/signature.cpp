#include "catch2/catch.hpp"

// Project includes
#include "crypto/signature.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("signature verify", "[crypto][sig]")
{
	auto secretKey = SecretKey("3ecb44df2159c26e0f995712d4f39b6f6e499b40749b1cf1246c37f9516cb6a4");
	auto publicKey = PublicKey(secretKey);

	auto msg = std::string("The quick brown fox jumps over the lazy dog.");
	auto msg_bad = std::string("The lazy brown fox jumps over the quick dog.");

	SECTION("libsecp256k1")
	{
		auto signature = Signature(secretKey, msg);

		SECTION("deterministic sign")
		{
			REQUIRE_THAT("5385685eef5fe0f2f93fa022002bb00f8b2478b9567618e47463cda72a78dcdb56a7a6bcd0bd79f709f15e0d3d53ba9909d4a3d100e25065bc0b7bd2537f39191c", Equals(signature.toHex()));
		}
		SECTION("recover")
		{
			auto recovered = signature.recover(msg);
			REQUIRE_THAT(publicKey.toHex(), Equals(recovered.toHex()));
		}
		SECTION("verify with pubkey")
		{
			auto result = signature.verify(msg, publicKey);
			REQUIRE(result);
			auto result_bad = signature.verify(msg_bad, publicKey);
			REQUIRE(!result_bad);
		}
		SECTION("verify with address")
		{
			auto result = signature.verify(msg, Address(publicKey));
			REQUIRE(result);
			auto result_bad = signature.verify(msg_bad, Address(publicKey));
			REQUIRE(!result_bad);
		}
	}
}