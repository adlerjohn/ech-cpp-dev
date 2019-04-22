#include "block_header.hpp"

using namespace ech;

const std::vector<std::byte> BlockHeader::serializeData(const crypto::Digest& root, const uint64_t height) const
{
	std::vector<std::byte> serial;

	static const size_t heightSize = 8u;
	std::stringstream buf;
	buf << std::hex << std::setfill('0') << std::setw(heightSize * 2) << height;
	const auto heightBytes = crypto::byteset<heightSize>(buf.str());
	serial.insert(serial.end(), heightBytes.begin(), heightBytes.end());

	serial.insert(serial.end(), root.begin(), root.end());

	return serial;
}

BlockHeader::BlockHeader(const crypto::Digest& root, const uint64_t height)
	: _id(crypto::Digest(serializeData(root, height)))
	, _root(root)
	, _height(height)
{
}

const std::vector<std::byte> BlockHeader::serialize() const
{
	std::vector<std::byte> serial;

	serial.insert(serial.end(), _id.begin(), _id.end());

	const auto serialData = serializeData(_root, _height);
	serial.insert(serial.end(), serialData.begin(), serialData.end());

	return serial;
}