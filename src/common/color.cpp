#include "color.hpp"

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