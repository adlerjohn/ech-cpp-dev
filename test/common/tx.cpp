#include "catch2/catch.hpp"

// Project includes
#include "common/tx.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("tx zero", "[common][tx]")
{
	const auto inputs = std::vector<Input>{};
	const auto outputs = std::vector<TXO>{};
	const auto witnesses = std::vector<crypto::Signature>{};
	const uint64_t heightMin = 0u;
	const uint64_t heightMax = 0u;
	const uint64_t recentBlockHeight = 0u;
	const auto recentBlockHash = crypto::Digest();

	const auto tx = TX(inputs, outputs, witnesses, heightMin, heightMax, recentBlockHeight, recentBlockHash);

	REQUIRE_THAT("74723bc3efaf59d897623890ae3912b9be3c4c67ccee3ffcf10b36406c722c1b", Equals(tx.getId().toHex()));
	REQUIRE(tx.getInputs().empty());
	REQUIRE(tx.getOutputs().empty());
	REQUIRE(tx.getWitnesses().empty());
	REQUIRE(0u == tx.getHeightMin());
	REQUIRE(0u == tx.getHeightMax());
	REQUIRE(0u == tx.getRecentBlockHeight());
	REQUIRE("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563" == tx.getRecentBlockHash().toHex());
	const auto golden = std::string(
		"74723bc3efaf59d897623890ae3912b9be3c4c67ccee3ffcf10b36406c722c1b" // tx id
		"00000000" // input count
		"00000000" // output count
		"00000000" // witnesses count
		"0000000000000000" // height min
		"0000000000000000" // height max
		"0000000000000000" // recent block height
		);
	REQUIRE_THAT(golden, Equals(tx.toHex()));
}

TEST_CASE("tx random", "[common][tx]")
{
	const auto digest = crypto::Digest("testing");
	const auto outpoint = Outpoint(TXID(digest), 42u);
	const auto input = Input(outpoint, 0u);
	const auto inputs = std::vector<Input>{input};

	const auto index = 1u;
	const auto recipient = crypto::Address("deadbeefdeadbeefdeadbeefdeadbeefdeadbeef");
	const auto amount = CoinAmount(42);
	const auto address = crypto::Address("8a40bfaa73256b60764c1bf40675a99083efb075");
	const auto color = Color(address);
	const auto txo = TXO(index, recipient, amount, color);
	const auto outputs = std::vector<TXO>{txo};

	// TODO add signature
	const auto witnesses = std::vector<crypto::Signature>{};

	const uint64_t heightMin = 42u;
	const uint64_t heightMax = 43u;
	const uint64_t recentBlockHeight = 7u;
	const auto recentBlockHash = crypto::Digest("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02", true);

	const auto tx = TX(inputs, outputs, witnesses, heightMin, heightMax, recentBlockHeight, recentBlockHash);

	REQUIRE_THAT("46819a2b140c0917513ce0fef454f9855752accbb31c16e5a3c9b8568477bb9c", Equals(tx.getId().toHex()));
	REQUIRE(1 == tx.getInputs().size());
	REQUIRE(1 == tx.getOutputs().size());
	// TODO add signature
	REQUIRE(tx.getWitnesses().empty());
	REQUIRE(42u == tx.getHeightMin());
	REQUIRE(43u == tx.getHeightMax());
	REQUIRE(7u == tx.getRecentBlockHeight());
	REQUIRE("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02" == tx.getRecentBlockHash().toHex());
	const auto golden = std::string(
		"46819a2b140c0917513ce0fef454f9855752accbb31c16e5a3c9b8568477bb9c" // tx id
		"00000001" // input count
        "5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b020000002a00000000" // inputs
		"00000001" // output count
        "00000001deadbeefdeadbeefdeadbeefdeadbeefdeadbeef000000000000000000000000000000000000000000000000000000000000002a018a40bfaa73256b60764c1bf40675a99083efb075" // outputs
		"00000000" // witnesses count
		"000000000000002a" // height min
		"000000000000002b" // height max
		"0000000000000007" // recent block height
		"5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02" // recent block hash
	);
	REQUIRE_THAT(golden, Equals(tx.toHex()));
}