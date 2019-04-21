#include "block.hpp"

// Project includes
#include "merkle.hpp"
#include "txid.hpp"

using namespace ech;

const std::vector<crypto::Digest> Block::toLeafHashes(const std::vector<Tx>& leaves)
{
	std::vector<crypto::Digest> leafHashes;

	for (const auto& leaf : leaves) {
		leafHashes.emplace_back(TXID(leaf.serialize()));
	}

	return leafHashes;
}

Block::Block(const std::vector<Tx>& leaves, const uint64_t height)
	: _header(MerkleTree(toLeafHashes(leaves)).getRoot(), height)
	, _leaves(leaves)
{
}

const std::vector<std::byte> ech::Block::serialize() const
{
	return std::vector<std::byte>();
}