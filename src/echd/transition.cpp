#include "transition.hpp"

using namespace ech;

Transition::Transition(const std::vector<UTXO>& add, const std::vector<UTXO>& remove)
	: _add(add)
	, _remove(remove)
{
}
