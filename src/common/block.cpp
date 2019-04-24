#include "block.hpp"

// Project includes
#include "deserializer.hpp"
#include "merkle.hpp"
#include "serializer.hpp"
#include "txid.hpp"

using namespace ech;

const std::vector<crypto::Digest> Block::toDepositHashes(const std::vector<Deposit>& deposits)
{
	std::vector<crypto::Digest> depositHashes;

	for (const auto& deposit : deposits) {
		depositHashes.emplace_back(crypto::Digest(deposit.serialize()));
	}

	return depositHashes;
}

const std::vector<crypto::Digest> Block::toLeafHashes(const std::vector<TX>& leaves)
{
	std::vector<crypto::Digest> leafHashes;

	for (const auto& leaf : leaves) {
		leafHashes.emplace_back(TXID(leaf.serialize()));
	}

	return leafHashes;
}

Block::Block(const uint32_t version, const crypto::Digest& prev, const std::vector<Deposit>& deposits, const std::vector<TX>& leaves, const uint64_t height)
	: _header(version, prev, MerkleTree(toDepositHashes(deposits)).getRoot(), MerkleTree(toLeafHashes(leaves)).getRoot(), height)
	, _deposits(deposits)
	, _leaves(leaves)
{
}

const Block Block::deserialize(std::deque<std::byte>& serial)
{
	const auto header = BlockHeader::deserialize(serial);

	std::vector<Deposit> deposits;
	const auto depositsCount = deserializer::deserialize<uint64_t, 8u>(serial);
	for (size_t i = 0; i < depositsCount; i++) {
		deposits.push_back(Deposit::deserialize(serial));
	}

	std::vector<TX> leaves;
	const auto leavesCount = deserializer::deserialize<uint64_t, 8u>(serial);
	for (size_t i = 0; i < leavesCount; i++) {
		leaves.push_back(TX::deserialize(serial));
	}

	return Block(header.getVersion(), header.getPreviousBlockHash(), deposits, leaves, header.getHeight());
}

const std::vector<std::byte> ech::Block::serialize() const
{
	std::vector<std::byte> serial;

	const auto headerSerialized = _header.serialize();
	serial.insert(serial.end(), headerSerialized.begin(), headerSerialized.end());

	const uint64_t depositCount = _deposits.size();
	const auto depositCountBytes = serializer::serialize<uint64_t, 8u>(depositCount);
	serial.insert(serial.end(), depositCountBytes.begin(), depositCountBytes.end());

	for (const auto& deposit : _deposits) {
		const auto depositBytes = deposit.serialize();
		serial.insert(serial.end(), depositBytes.begin(), depositBytes.end());
	}

	const uint64_t leafCount = _leaves.size();
	const auto leafCountBytes = serializer::serialize<uint64_t, 8u>(leafCount);
	serial.insert(serial.end(), leafCountBytes.begin(), leafCountBytes.end());

	for (const auto& leaf : _leaves) {
		const auto leafBytes = leaf.serialize();
		serial.insert(serial.end(), leafBytes.begin(), leafBytes.end());
	}

	return serial;
}