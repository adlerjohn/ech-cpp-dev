#include "outpoint.hpp"

using namespace ech;

Outpoint::Outpoint(const TXID& txid, const uint32_t index)
	: _txid(txid)
	, _index(index)
{
}

const std::vector<std::byte> Outpoint::serialize() const
{
	std::vector<std::byte> serial;

	serial.insert(serial.end(), _txid.begin(), _txid.end());

	const auto indexBytes = Serializable::serialize(_index);
	serial.insert(serial.end(), indexBytes.begin(), indexBytes.end());

	return serial;
}