#include "block.hpp"

// Project includes
#include "merkle.hpp"

using namespace ech;

const std::vector<crypto::Digest> Block::toLeafHashes(std::vector<Tx> leaves)
{
	// TODO implement
	return std::vector<crypto::Digest>();
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