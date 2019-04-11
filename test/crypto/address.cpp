#include "catch2/catch.hpp"

// Project includes
#include "crypto/address.hpp"

using namespace ech::crypto;
using Catch::Matchers::Equals;

TEST_CASE("address zero", "[crypto][addr]")
{
	auto addr = Address(std::string(64*2, '0'));
	REQUIRE_THAT("3f17f1962b36e491b30a40b2405849e597ba5fb5", Equals(addr.toHex()));
}

TEST_CASE("from public key (aleth example)", "[crypto][addr]")
{
	auto addr = Address("97466f2b32bc3bb76d4741ae51cd1d8578b48d3f1e68da206d47321aec267ce78549b514e4453d74ef11b0cd5e4e4c364effddac8b51bcfc8de80682f952896f");
	REQUIRE_THAT("8a40bfaa73256b60764c1bf40675a99083efb075", Equals(addr.toHex()));
}

TEST_CASE("from public key (random)", "[crypto][addr]")
{
	auto addr = Address("8eaae4388255152e18f6dfff6a011ce571c4eaad8789d152d8ae58e6db69fe9c427921be60c741e9b8988ff8b792ea20496f9c89f55decd65cf04c0b75d6e949");
	REQUIRE_THAT("f8414179bf83c616cdaf5fc43294aa447efea2b0", Equals(addr.toHex()));
}