#include "merkle.hpp"

using namespace ech;

const crypto::Digest MerkleTree::calculateRoot(const std::vector<crypto::Digest>& leaves) const
{
	// Special case: if the tree is empty, return the hash of 0
	if (leaves.empty())
		return crypto::Digest("0000000000000000000000000000000000000000000000000000000000000000");

	return crypto::Digest("");
}

MerkleTree::MerkleTree(const std::vector<crypto::Digest>& leaves)
	: _root(calculateRoot(leaves))
{
}