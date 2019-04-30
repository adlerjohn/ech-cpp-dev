#pragma once

// Project includes
#include "crypto/digest.hpp"

namespace ech
{

/**
 * Fixed Merkle tree structure.
 */
class MerkleTree
{
private:
	const crypto::Digest _root;

	const crypto::Digest calculateRoot(const std::vector<crypto::Digest>& leaves) const;

public:
	explicit MerkleTree(const std::vector<crypto::Digest>& leaves);

	[[nodiscard]] const auto& getRoot() const { return this->_root; }

	/**
	 * Checks a Merkle proof against this tree.
	 * @param leaf Leaf node to check for inclusion.
	 * @param branch Merkle branch proof. Each node is paired with a Boolean, isLeft, indicating if the node is on the left.
	 * @return True is the proof is valid, false otherwise.
	 */
	[[nodiscard]] const bool checkProof(const crypto::Digest& leaf, const std::vector<std::pair<bool, crypto::Digest>>& branch) const;
};

} // namespace ech