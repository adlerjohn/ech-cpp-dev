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
	return Address();
}

CoinAmount UTXO::getAmount() const
{
	return CoinAmount();
}

bool UTXO::isColored() const
{
	return false;
}
