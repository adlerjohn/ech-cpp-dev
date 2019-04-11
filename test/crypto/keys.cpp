#include "catch2/catch.hpp"

// Project includes
#include "crypto/keys.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("keys empty", "[crypto][keys]")
{
	auto str = std::string(SecretKey::size()*2, '0');
	auto sk = SecretKey(str);
	REQUIRE_THAT(str, Equals(sk.toHex()));
}