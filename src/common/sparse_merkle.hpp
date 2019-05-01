#pragma once

// Project includes
#include "crypto/digest.hpp"

namespace ech
{

class SparseMerkleTree
{
private:
	/**
	 * Optimization: hash(0, 0) = 0, so we don't need to pre-compute defaults.
	 * @return Digest for empty node.
	 */
	[[nodiscard]] static const auto emptyNode();

public:
};

} // namespace ech