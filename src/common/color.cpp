#include "color.hpp"

using namespace ech;

Color::Color()
	: _isColored(false)
	, _id(crypto::Address(std::string()))
{
}

Color::Color(const crypto::Address& id)
	: _isColored(true)
	, _id(id)
{
}

const std::vector<std::byte> Color::serialize() const
{
	// TODO implement
	return std::vector<std::byte>();
}
