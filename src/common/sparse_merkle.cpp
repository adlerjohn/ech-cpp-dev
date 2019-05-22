#include "sparse_merkle.hpp"

using namespace ech;

const auto SparseMerkleTree::keyToPath(const crypto::Digest& key)
{
	std::vector<bool> path;

	static const auto zero = std::byte(0);
	static const auto one = std::byte(1);

	path.reserve(crypto::Digest::size() * 8u);
	for (const auto& byte : key) {
		// 8 bits in a byte
		for (auto i = 0u; i < 8u; i++) {
			path.push_back((byte & one << i) == zero);
		}
	}

	return path;
}

SMTNode::SMTNode(const crypto::Digest& digest)
	: _digest(digest)
{
}

const crypto::Digest SparseMerkleTree::defaultNodeValue()
{
	return crypto::Digest("0000000000000000000000000000000000000000000000000000000000000000", true);
}

SparseMerkleTree::SparseMerkleTree()
	: _root(std::make_unique<SMTNode>(defaultNodeValue()))
{
}

const bool SparseMerkleTree::at(const crypto::Digest& key) const
{
	if (_root == nullptr) {
		return false;
	}

	const auto path = keyToPath(key);
	auto val = false;

	auto node = _root.get();
	for (const auto& isLeft : path) {
		if (node->isLeaf()) {
			if (node->getDigest() == key) {
				val = true;
			}
			break;
		}

		if (isLeft) {
			node = node->getLeft().get();
		} else {
			node = node->getRight().get();
		}
	}

	return val;
}

const void SparseMerkleTree::insert(const crypto::Digest& key)
{
	return;
}

const void SparseMerkleTree::erase(const crypto::Digest& key)
{
	return;
}

const auto SparseMerkleTree::getInclusionProof(const crypto::Digest& key) const
{
	std::vector<std::optional<crypto::Digest>> path;

	return path;
}

const auto SparseMerkleTree::getExclusionProof(const crypto::Digest& key) const
{
	std::vector<std::optional<crypto::Digest>> path;

	return path;
}

const bool SparseMerkleTree::checkInclusionProof(const std::vector<bool>& path, const std::vector<std::optional<crypto::Digest>>& hashes) const
{
	return false;
}

const bool SparseMerkleTree::checkExclusionProof(const std::vector<bool>& path, const std::vector<std::optional<crypto::Digest>>& hashes) const
{
	return false;
}
