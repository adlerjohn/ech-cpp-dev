#include "catch2/catch.hpp"

// Project includes
#include "common/tx.hpp"

using namespace ech;
using Catch::Matchers::Equals;

TEST_CASE("tx data zero", "[common][txdata]")
{
	const auto inputs = std::vector<Input>{};
	const auto outputs = std::vector<TXO>{};
	const uint64_t heightMin = 0u;
	const uint64_t heightMax = 0u;
	const uint64_t recentBlockHeight = 0u;
	const auto recentBlockHash = crypto::Digest();

	const auto data = TXData(inputs, outputs, heightMin, heightMax, recentBlockHeight, recentBlockHash);

	REQUIRE_THAT("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563", Equals(data.getId().toHex()));
	REQUIRE(data.getInputs().empty());
	REQUIRE(data.getOutputs().empty());
	REQUIRE(0u == data.getHeightMin());
	REQUIRE(0u == data.getHeightMax());
	REQUIRE(0u == data.getRecentBlockHeight());
	REQUIRE("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563" == data.getRecentBlockHash().toHex());
	const auto golden = std::string(
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563" // tx id
		"00000000" // input count
		"00000000" // output count
		"0000000000000000" // height min
		"0000000000000000" // height max
		"0000000000000000" // recent block height
	);
	REQUIRE_THAT(golden, Equals(data.toHex()));
}

TEST_CASE("tx data random", "[common][txdata]")
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

	const uint64_t heightMin = 42u;
	const uint64_t heightMax = 43u;
	const uint64_t recentBlockHeight = 7u;
	const auto recentBlockHash = crypto::Digest("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02", true);

	const auto data = TXData(inputs, outputs, heightMin, heightMax, recentBlockHeight, recentBlockHash);

	REQUIRE_THAT("c775ddaec0393580f18b18ef583cbad1d449a590a685fce908b03a469f00f190", Equals(data.getId().toHex()));
	REQUIRE(1u == data.getInputs().size());
	REQUIRE(1u == data.getOutputs().size());
	REQUIRE(42u == data.getHeightMin());
	REQUIRE(43u == data.getHeightMax());
	REQUIRE(7u == data.getRecentBlockHeight());
	REQUIRE("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02" == data.getRecentBlockHash().toHex());
	const auto golden = std::string(
		"c775ddaec0393580f18b18ef583cbad1d449a590a685fce908b03a469f00f190" // tx id
		"00000001" // input count
		"5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b020000002a00000000" // inputs
		"00000001" // output count
		"00000001deadbeefdeadbeefdeadbeefdeadbeefdeadbeef000000000000000000000000000000000000000000000000000000000000002a018a40bfaa73256b60764c1bf40675a99083efb075" // outputs
		"000000000000002a" // height min
		"000000000000002b" // height max
		"0000000000000007" // recent block height
		"5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02" // recent block hash
	);
	REQUIRE_THAT(golden, Equals(data.toHex()));
}

TEST_CASE("tx zero", "[common][tx]")
{
	const auto inputs = std::vector<Input>{};
	const auto outputs = std::vector<TXO>{};
	const uint64_t heightMin = 0u;
	const uint64_t heightMax = 0u;
	const uint64_t recentBlockHeight = 0u;
	const auto recentBlockHash = crypto::Digest();
	const auto data = TXData(inputs, outputs, heightMin, heightMax, recentBlockHeight, recentBlockHash);

	const auto witnesses = std::vector<crypto::Signature>{};
	const auto tx = TX(data, witnesses);

	REQUIRE_THAT("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563", Equals(tx.getData().getId().toHex()));
	REQUIRE(tx.getData().getInputs().empty());
	REQUIRE(tx.getData().getOutputs().empty());
	REQUIRE(tx.getWitnesses().empty());
	REQUIRE(0u == tx.getData().getHeightMin());
	REQUIRE(0u == tx.getData().getHeightMax());
	REQUIRE(0u == tx.getData().getRecentBlockHeight());
	REQUIRE("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563" == tx.getData().getRecentBlockHash().toHex());
	const auto golden = std::string(
		"290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563" // tx id
		"00000000" // input count
		"00000000" // output count
		"0000000000000000" // height min
		"0000000000000000" // height max
		"0000000000000000" // recent block height
		"00000000" // witnesses count
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

	const uint64_t heightMin = 42u;
	const uint64_t heightMax = 43u;
	const uint64_t recentBlockHeight = 7u;
	const auto recentBlockHash = crypto::Digest("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02", true);

	const auto data = TXData(inputs, outputs, heightMin, heightMax, recentBlockHeight, recentBlockHash);

	SECTION("random signature")
	{
		const auto signature = crypto::Signature("5385685eef5fe0f2f93fa022002bb00f8b2478b9567618e47463cda72a78dcdb56a7a6bcd0bd79f709f15e0d3d53ba9909d4a3d100e25065bc0b7bd2537f39191c");
		const auto witnesses = std::vector<crypto::Signature>{signature};
		const auto tx = TX(data, witnesses);

		REQUIRE_THAT("c775ddaec0393580f18b18ef583cbad1d449a590a685fce908b03a469f00f190", Equals(tx.getData().getId().toHex()));
		REQUIRE(1u == tx.getData().getInputs().size());
		REQUIRE(1u == tx.getData().getOutputs().size());
		REQUIRE(1u == tx.getWitnesses().size());
		REQUIRE(42u == tx.getData().getHeightMin());
		REQUIRE(43u == tx.getData().getHeightMax());
		REQUIRE(7u == tx.getData().getRecentBlockHeight());
		REQUIRE("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02" == tx.getData().getRecentBlockHash().toHex());
		const auto golden = std::string(
			"c775ddaec0393580f18b18ef583cbad1d449a590a685fce908b03a469f00f190" // tx id
			"00000001" // input count
			"5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b020000002a00000000" // inputs
			"00000001" // output count
			"00000001deadbeefdeadbeefdeadbeefdeadbeefdeadbeef000000000000000000000000000000000000000000000000000000000000002a018a40bfaa73256b60764c1bf40675a99083efb075" // outputs
			"000000000000002a" // height min
			"000000000000002b" // height max
			"0000000000000007" // recent block height
			"5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02" // recent block hash
			"00000001" // witnesses count
			"5385685eef5fe0f2f93fa022002bb00f8b2478b9567618e47463cda72a78dcdb56a7a6bcd0bd79f709f15e0d3d53ba9909d4a3d100e25065bc0b7bd2537f39191c" // witnesses
		);
		REQUIRE_THAT(golden, Equals(tx.toHex()));
	}

	SECTION("correct signature checking")
	{
		const auto secretKey = crypto::SecretKey("3ecb44df2159c26e0f995712d4f39b6f6e499b40749b1cf1246c37f9516cb6a4");
		const auto signature = crypto::Signature(secretKey, data.serialize());
		const auto witnesses = std::vector<crypto::Signature>{signature};
		const auto tx = TX(data, witnesses);

		const auto publicKey = crypto::PublicKey(secretKey);

		REQUIRE_THAT("c775ddaec0393580f18b18ef583cbad1d449a590a685fce908b03a469f00f190", Equals(tx.getData().getId().toHex()));
		REQUIRE(1u == tx.getData().getInputs().size());
		REQUIRE(1u == tx.getData().getOutputs().size());
		REQUIRE(1u == tx.getWitnesses().size());
		REQUIRE(42u == tx.getData().getHeightMin());
		REQUIRE(43u == tx.getData().getHeightMax());
		REQUIRE(7u == tx.getData().getRecentBlockHeight());
		REQUIRE("5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02" == tx.getData().getRecentBlockHash().toHex());
		const auto golden = std::string(
			"c775ddaec0393580f18b18ef583cbad1d449a590a685fce908b03a469f00f190" // tx id
			"00000001" // input count
			"5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b020000002a00000000" // inputs
			"00000001" // output count
			"00000001deadbeefdeadbeefdeadbeefdeadbeefdeadbeef000000000000000000000000000000000000000000000000000000000000002a018a40bfaa73256b60764c1bf40675a99083efb075" // outputs
			"000000000000002a" // height min
			"000000000000002b" // height max
			"0000000000000007" // recent block height
			"5f16f4c7f149ac4f9510d9cf8cf384038ad348b3bcdc01915f95de12df9d1b02" // recent block hash
			"00000001" // witnesses count
			"3ecc418cdbb3a428e3b7bda8b98020468f60bbfa8f13a6613ed7f3e0d6a350224fa39402330614af7db257630cfca23a5f6945f0d44aed4d592aa3858093018d1b" // witnesses
		);
		REQUIRE_THAT(golden, Equals(tx.toHex()));
		REQUIRE(signature.verify(crypto::Digest(data.serialize()), crypto::Address(publicKey)));
	}
}