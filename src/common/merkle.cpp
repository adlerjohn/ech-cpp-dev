#include "merkle.hpp"

using namespace ech;

const crypto::Digest MerkleTree::calculateRoot(const std::vector<crypto::Digest>& leaves) const
{
	// Special case: if the tree is empty, return the hash of 0
	if (leaves.empty()) {
		const auto zeroes = std::vector<std::byte>(32, std::byte(0x00));
		return crypto::Digest(zeroes);
	}

	auto hashesPrev = leaves;

	while (hashesPrev.size() > 1) {
		if (hashesPrev.size() % 2 == 1)
			hashesPrev.push_back(hashesPrev.back());

		std::vector<crypto::Digest> hashesNext;
		hashesNext.reserve(hashesPrev.size() / 2);
		for (size_t i = 0; i < hashesPrev.size() / 2; i++)
			hashesNext.push_back(hashesPrev.at(i*2) + hashesPrev.at(i*2+1));

		hashesPrev.swap(hashesNext);
	}

	return hashesPrev.front();
}

MerkleTree::MerkleTree(const std::vector<crypto::Digest>& leaves)
	: _root(calculateRoot(leaves))
{
}