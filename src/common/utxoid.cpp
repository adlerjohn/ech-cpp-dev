#include "utxoid.hpp"

using namespace ech;

UTXOID::UTXOID(const Outpoint& outpoint)
	: crypto::Digest(outpoint.serialize())
{
}