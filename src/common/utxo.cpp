#include "utxo.hpp"

using namespace ech;

UTXO::UTXO() :
		_id(),
		_owner(std::string()),
		_amount(),
		_color()
{
}