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
};

} // namespace ech