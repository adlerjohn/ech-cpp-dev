#include "catch2/catch.hpp"

// TODO remove
#include <iostream>

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

	auto digest = Digest(msg);

	SECTION("sign message")
	{
		auto sig = secretKey.sign(msg);
		std::cout << sig.length() << " " << sig << std::endl;
		auto signature = Signature(sig);
		std::cout << signature.size() << " " << signature.toHex() << std::endl;
//		auto recovered = signature.recover();
//		std::cout << recovered.size() << " " << recovered.toHex() << std::endl;
//		REQUIRE_THAT(publicKey.toHex(), Equals(recovered.toHex()));
		auto result = signature.verify(msg, publicKey);
		REQUIRE(result);
		auto result_bad = signature.verify(msg_bad, publicKey);
		REQUIRE(!result_bad);
	}
	SECTION("sign digest")
	{
		auto sig = secretKey.sign(digest);
		std::cout << sig.length() << " " << sig << std::endl;
		auto signature = Signature(sig);
		std::cout << signature.size() << " " << signature.toHex() << std::endl;
//		auto recovered = signature.recover();
//		std::cout << recovered.size() << " " << recovered.toHex() << std::endl;
//		REQUIRE_THAT(publicKey.toHex(), Equals(recovered.toHex()));
		auto result = signature.verify(msg, publicKey);
		REQUIRE(result);
		auto result_bad = signature.verify(msg_bad, publicKey);
		REQUIRE(!result_bad);
	}
}