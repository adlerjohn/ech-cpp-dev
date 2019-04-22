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
	REQUIRE(tx.getInputs().empty());
	REQUIRE(tx.getOutputs().empty());
	REQUIRE(tx.getWitnesses().empty());
	REQUIRE(0u == tx.getHeightMin());
	REQUIRE(0u == tx.getHeightMax());
	REQUIRE(0u == tx.getRecentBlockHeight());
	REQUIRE("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563" == tx.getRecentBlockHash().toHex());
}