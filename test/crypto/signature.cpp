#include "catch2/catch.hpp"

// Project includes
#include "crypto/signature.hpp"

using namespace ech::crypto;

TEST_CASE("Signature length", "[sig-len]")
{
	REQUIRE_THROWS_AS(Signature(std::string()), std::invalid_argument);
}