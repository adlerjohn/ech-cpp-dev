#include "catch2/catch.hpp"

// Project includes
#include "crypto/signature.hpp"

using namespace ech::crypto;

TEST_CASE("signature verify", "[crypto][sig]")
{
	auto sk = SecretKey("3ecb44df2159c26e0f995712d4f39b6f6e499b40749b1cf1246c37f9516cb6a4");
	auto pk = PublicKey(sk);

	auto msg = std::string("The quick brown fox jumps over the lazy dog.");

	SECTION("sign message")
	{
		auto sig = Signature(sk.sign(msg));
		auto result = sig.verify(msg, pk);
		REQUIRE(result);
	}
	SECTION("sign digest")
	{
		auto digest = Digest(msg);
		auto sig = Signature(sk.sign(digest));
		auto result = sig.verify(msg, pk);
		REQUIRE(result);
	}
}