#include "consensus.hpp"

// System includes
#include <random>

// Project includes
#include "echd/consensus.hpp"

using namespace ech::benchmark;

void ConsensusBenchmark::setup()
{
	constexpr auto halfCount = _count / 2u;
	constexpr auto hexes = std::string_view("0123456789abcdef");

	auto rng = std::mt19937(0);
	auto distHexes = std::uniform_int_distribution<std::mt19937::result_type>(0, 15);

	// Create a bunch of secret keys we can use to sign
	for (size_t i = 0; i < _addressCount; i++) {
		std::string key;
		for (size_t j = 0; j < crypto::SecretKey::size() * 2; j++) {
			const auto c = hexes.at(distHexes(rng));
			key.push_back(c);
		}
		const auto secretKey = crypto::SecretKey(key);
		_secretKeys.push_back(secretKey);
		const auto address = crypto::Address(crypto::PublicKey(secretKey));
		_addresses.push_back(address);
	}

	auto consensus = Consensus();

	auto distAddresses = std::uniform_int_distribution<std::mt19937::result_type>(0, _addressCount - 1);

	// Create half of count blocks as pure deposits, to set up the state
	for (size_t i = 0; i < halfCount; i++) {
		std::vector<Deposit> deposits;
		for (size_t j = 0; j < _blockTxCount; j++) {
			const auto& owner = _addresses.at(distAddresses(rng));
			const auto deposit = Deposit(owner, 1000u, Color(), i + 1, j);
			deposits.push_back(deposit);
		}
		std::vector<TX> leaves;
		const auto block = Block(1, (i == 0) ? crypto::Digest() : _data.back().getHeader().getId(), deposits, leaves, i + 1);
		_data.push_back(block);
		consensus.appendBlock(block, consensus.getBlockTransition(block).value());
	}

	// Create half of count blocks as pure transactions
	for (size_t i = 0; i < halfCount; i++) {
		std::vector<Deposit> deposits;
		std::vector<TX> leaves;
		const auto& utxoSet = consensus.getState().data();
		auto dist = std::uniform_int_distribution<std::mt19937::result_type>(0, utxoSet.size() - 1);
		for (size_t j = 0; j < _blockTxCount; j++) {
			// Select random UTXO to spend
			auto it = utxoSet.begin();
			std::advance(it, dist(rng));
			const auto& utxo = it->second;

			const auto& recipient = _addresses.at(distAddresses(rng));
			const auto inputs = std::vector<Input>{Input(utxo.getOutpoint(), 0)};
			const auto outputs = std::vector<TXO>{TXO(0, recipient, 1000, Color())};
			const auto txdata = TXData(1, inputs, outputs, 0, 0, 0, crypto::Digest());

			std::vector<crypto::Signature> witnesses;
			// TODO sign transactions
			const auto tx = TX(txdata, witnesses);
			leaves.push_back(tx);
		}
		const auto block = Block(1, _data.back().getHeader().getId(), deposits, leaves, halfCount + i + 1);
		_data.push_back(block);
		consensus.appendBlock(block, consensus.getBlockTransition(block, true).value());
	}
}

void ConsensusBenchmark::run()
{
	this->before();

	for (auto& block : _data) {
		const auto result = _consensus.getBlockTransition(block, true);
		if (result) {
			_passed++;
			_consensus.appendBlock(block, result.value());
		}
	}

	this->after();
}

int main()
{
	std::cout << "Setting up consensus tests for " << ConsensusBenchmark::count() << " blocks..." << std::endl;
	auto consensus = ConsensusBenchmark();
	consensus.setup();
	std::cout << "Consensus setup complete for " << ConsensusBenchmark::countTransactions() << " transactions..." << std::endl;
	std::cout << std::endl;

	std::cout << "Running single-threaded benchmarking..." << std::endl;
	consensus.run();
	std::cout << "Complete in " << consensus.getDuration() << "ms." << std::endl;
	consensus.reset();
	std::cout << std::endl;

	return 0;
}