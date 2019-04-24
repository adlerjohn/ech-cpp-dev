#include "input.hpp"

// Project includes
#include "serializer.hpp"

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

	const auto indexBytes = serializer::serialize<uint32_t, 4u>(_witnessIndex);
	serial.insert(serial.end(), indexBytes.begin(), indexBytes.end());

	return serial;
}