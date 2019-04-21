#include "tx.hpp"

using namespace ech;

bool Tx::verify(const State& state) const
{
	// To verify a transaction is valid, we need to
	// 1) for each input
	//  a) recover the address from the signature, using tx data hash
	//  b) check that the UTXO being spent exists in the state and owner matches
	// 2) sum inputs <= sum outputs (including colored coins)
	return false;
}
const std::vector<std::byte> Tx::serialize() const
{
	// TODO implement
	return std::vector<std::byte>();
}
