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

	static const size_t indexSize = 4u;
	std::stringstream buf;
	buf << std::hex << std::setfill('0') << std::setw(indexSize * 2) << _index;
	const auto indexBytes = crypto::byteset<indexSize>(buf.str());
	serial.insert(serial.end(), indexBytes.begin(), indexBytes.end());

	return serial;
}