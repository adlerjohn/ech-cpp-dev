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

	SECTION("sign message")
	{
		auto signature = Signature(msg, secretKey);

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
		SECTION("verify directly")
		{
			auto result = signature.verify_direct(msg, publicKey);
			REQUIRE(result);
			auto result_bad = signature.verify_direct(msg_bad, publicKey);
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