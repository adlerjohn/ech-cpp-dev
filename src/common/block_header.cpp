#include "block_header.hpp"

using namespace ech;

// TODO compute ID
BlockHeader::BlockHeader(const crypto::Digest& root, const uint64_t height)
	: _id()
	, _root(root)
	, _height(height)
{
}

const std::vector<std::byte> BlockHeader::serialize() const
{
	return std::vector<std::byte>();
}