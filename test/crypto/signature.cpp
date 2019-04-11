#include "catch2/catch.hpp"

// Project includes
#include "crypto/signature.hpp"

using namespace ech::crypto;

TEST_CASE("signature length", "[crypto][sig]")
{
	REQUIRE_THROWS_AS(Signature(std::string()), std::invalid_argument);
}