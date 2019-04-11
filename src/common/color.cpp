#include "color.hpp"

using namespace ech;
using namespace ech::crypto;

Color::Color()
	: _isColored(false)
	, _id(Address(std::string()))
{
}

Color::Color(Address id)
	: _isColored(true)
	, _id(id)
{
}