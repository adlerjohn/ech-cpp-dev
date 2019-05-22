#pragma once

// Project includes
#include "crypto/digest.hpp"

namespace ech
{

class SMTNode
{
private:
	crypto::Digest _digest;

	std::unique_ptr<SMTNode> _parent = nullptr;
	std::unique_ptr<SMTNode> _left = nullptr;
	std::unique_ptr<SMTNode> _right = nullptr;

public:
	explicit SMTNode(const crypto::Digest& digest);

	~SMTNode() {
		_left.reset();
		_right.reset();
	}

	[[nodiscard]] const auto& getDigest() const { return _digest; }
	[[nodiscard]] const bool hasLeft() const { return _left == nullptr; }
	[[nodiscard]] const bool hasRight() const { return _right == nullptr; }
	[[nodiscard]] const bool isLeaf() const { return !(hasLeft() || hasRight()); }
	[[nodiscard]] const auto& getLeft() const { return _left; }
	[[nodiscard]] const auto& getRight() const { return _right; }
};

/**
 * Optimized sparse Merkle tree structure. Represent subtrees with one leaf as
 * just a single node with metadata.
 */
class SparseMerkleTree
{
private:
	std::unique_ptr<SMTNode> _root;

	/**
	 * Optimization: hash(0, 0) = 0, so we don't need to pre-compute defaults.
	 * @return Digest for default node.
	 */
	[[nodiscard]] static const crypto::Digest defaultNodeValue();

	[[nodiscard]] static const auto keyToPath(const crypto::Digest& key);

public:
	SparseMerkleTree();

	~SparseMerkleTree() {
		_root.reset();
	}

	[[nodiscard]] const auto getRoot() const { return _root->getDigest(); }

	const void insert(const crypto::Digest& key);

	const void erase(const crypto::Digest& key);

	[[nodiscard]] const bool at(const crypto::Digest& key) const;

	[[nodiscard]] const auto getInclusionProof(const crypto::Digest& key) const;

	[[nodiscard]] const auto getExclusionProof(const crypto::Digest& key) const;

	[[nodiscard]] const bool checkInclusionProof(const std::vector<bool>& path, const std::vector<std::optional<crypto::Digest>>& hashes) const;

	[[nodiscard]] const bool checkExclusionProof(const std::vector<bool>& path, const std::vector<std::optional<crypto::Digest>>& hashes) const;
};

} // namespace ech