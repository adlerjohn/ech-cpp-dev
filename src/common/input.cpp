#include "input.hpp"

using namespace ech;

Input::Input(const Outpoint& outpoint, const uint32_t witnessIndex)
	: _outpoint(outpoint)
	, _witnessIndex(witnessIndex)
{
}

const std::vector<std::byte> Input::serialize() const
{
	std::vector<std::byte> serial;

	const auto outpointSerialized = _outpoint.serialize();
	serial.insert(serial.end(), outpointSerialized.begin(), outpointSerialized.end());

	static const size_t indexSize = 4u;
	std::stringstream buf;
	buf << std::hex << std::setfill('0') << std::setw(indexSize * 2) << _witnessIndex;
	const auto indexBytes = crypto::byteset<indexSize>(buf.str());
	serial.insert(serial.end(), indexBytes.begin(), indexBytes.end());

	return serial;
}