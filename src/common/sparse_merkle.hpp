#pragma once

// Project includes
#include "crypto/digest.hpp"

namespace ech
{

class SMTNode
{
private:
	crypto::Digest _digest;

	std::unique_ptr<SMTNode> _left = nullptr;
	std::unique_ptr<SMTNode> _right = nullptr;

public:
	explicit SMTNode(const crypto::Digest& digest);

	[[nodiscard]] const auto& getDigest() const { return this->_digest; }
};

class SparseMerkleTree
{
private:
	std::unique_ptr<SMTNode> _root;

	/**
	 * Optimization: hash(0, 0) = 0, so we don't need to pre-compute defaults.
	 * @return Digest for default node.
	 */
	[[nodiscard]] static const crypto::Digest defaultNodeValue();

public:
	SparseMerkleTree();

	[[nodiscard]] const auto getRoot() const { return this->_root->getDigest(); }

	const void insert(const crypto::Digest& key);

	const void erase(const crypto::Digest& key);

	[[nodiscard]] const auto getInclusionProof(const crypto::Digest& key) const;

	[[nodiscard]] const auto getExclusionProof(const crypto::Digest& key) const;

	[[nodiscard]] const bool checkInclusionProof(const std::vector<std::pair<bool, crypto::Digest>>& path) const;

	[[nodiscard]] const bool checkExclusionProof(const std::vector<std::pair<bool, crypto::Digest>>& path) const;
};

} // namespace ech