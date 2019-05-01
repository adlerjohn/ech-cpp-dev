#include "sparse_merkle.hpp"

using namespace ech;

const auto SparseMerkleTree::emptyNode()
{
	return crypto::Digest("0000000000000000000000000000000000000000000000000000000000000000", true);
}