#include "block_header.hpp"

using namespace ech;

BlockHeader::BlockHeader(const crypto::Digest& root, const uint64_t height)
	: _id(crypto::Digest(serialize()))
	, _root(root)
	, _height(height)
{
}

const std::vector<std::byte> BlockHeader::serialize() const
{
	// TODO implement
	return std::vector<std::byte>();
}