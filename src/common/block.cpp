#include "block.hpp"

using namespace ech;

Block::Block(const std::vector<Tx>& leaves, const uint64_t height)
	: _header(leaves, height)
	, _leaves(leaves)
{
}

const std::vector<std::byte> ech::Block::serialize() const
{
	return std::vector<std::byte>();
}
