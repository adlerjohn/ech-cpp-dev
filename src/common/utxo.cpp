#include "utxo.hpp"

using namespace ech;

UTXO::UTXO()
	: _id(UTXOID(std::string(64u, '0')))
	, _owner(std::string())
	, _amount()
	, _color()
{
}