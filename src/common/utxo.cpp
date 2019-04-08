#include "utxo.hpp"

UTXO::UTXO() :
		_id(),
		_owner(),
		_amount(),
		_color()
{
}

UTXOID UTXO::getId() const
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
