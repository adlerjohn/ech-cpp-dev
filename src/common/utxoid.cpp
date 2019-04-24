#include "utxoid.hpp"

using namespace ech;

UTXOID::UTXOID(const std::array<std::byte, UTXOID::size()>& bytes)
	: crypto::Digest(bytes)
{
}

UTXOID::UTXOID(const Outpoint& outpoint)
	: crypto::Digest(outpoint.serialize())
{
}