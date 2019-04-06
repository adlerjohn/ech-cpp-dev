#include "color.hpp"

Color::Color() :
	_isColored(false),
	_id(Address())
{
}

Color::Color(Address id) :
	_isColored(true),
	_id(id)
{
}

bool Color::isColored() const
{
	return this->_isColored;
}

Address Color::getColor() const
{
	return this->_id;
}
