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

	const auto indexBytes = Serializable::serialize(_witnessIndex);
	serial.insert(serial.end(), indexBytes.begin(), indexBytes.end());

	return serial;
}