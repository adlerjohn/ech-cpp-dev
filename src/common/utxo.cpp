#include "utxo.hpp"

UTXO::UTXO() :
		_id(0),
		_owner(),
		_amount(),
		_color()
{
}

uint64_t UTXO::getId() const
{
	return _id;
}

Address UTXO::getOwner() const
{
	return 0;
}

CoinAmount UTXO::getAmount() const
{
	return 0;
}

bool UTXO::isColored() const
{
	return false;
}
