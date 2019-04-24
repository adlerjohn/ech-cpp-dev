#include "color.hpp"

// Project includes
#include "deserializer.hpp"

using namespace ech;

Color::Color()
	: _isColored(false)
	, _id(crypto::Address())
{
}

Color::Color(const crypto::Address& id)
	: _isColored(true)
	, _id(id)
{
}

const Color Color::deserialize(std::vector<std::byte>& serial)
{
	const auto isColored = static_cast<bool>(deserializer::deserialize<uint8_t, 1u>(serial));
	if (!isColored) {
		return Color();
	}

	const auto address = deserializer::move<crypto::Address>(serial);
	return Color(address);
}

const std::vector<std::byte> Color::serialize() const
{
	std::vector<std::byte> serial;

	if (_isColored) {
		serial.push_back(std::byte(0x01));
		serial.insert(serial.end(), _id.begin(), _id.end());
	} else {
		serial.push_back(std::byte(0x00));
	}

	return serial;
}