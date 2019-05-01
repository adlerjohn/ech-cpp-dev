#include "sparse_merkle.hpp"

using namespace ech;

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

const void SparseMerkleTree::insert(const crypto::Digest& value)
{
	return;
}

const void SparseMerkleTree::erase(const crypto::Digest& value)
{
	return;
}

const auto SparseMerkleTree::getInclusionProof(const crypto::Digest& key) const
{
	return nullptr;
}

const auto SparseMerkleTree::getExclusionProof(const crypto::Digest& key) const
{
	return nullptr;
}

const bool SparseMerkleTree::checkInclusionProof(const std::vector<std::pair<bool, crypto::Digest>>& path) const
{
	return 0;
}

const bool SparseMerkleTree::checkExclusionProof(const std::vector<std::pair<bool, crypto::Digest>>& path) const
{
	return 0;
}