#include "outpoint.hpp"

// Project includes
#include "deserializer.hpp"
#include "serializer.hpp"

using namespace ech;

Outpoint::Outpoint(const TXID& txid, const uint32_t index)
	: _txid(txid)
	, _index(index)
{
}

const Outpoint Outpoint::deserialize(std::deque<std::byte>& serial)
{
	const auto txid = deserializer::move<TXID>(serial);

	const auto index = deserializer::deserialize<uint32_t, 4u>(serial);

	return Outpoint(txid, index);
}

const std::vector<std::byte> Outpoint::serialize() const
{
	std::vector<std::byte> serial;

	serial.insert(serial.end(), _txid.begin(), _txid.end());

	const auto indexBytes = serializer::serialize<uint32_t, 4u>(_index);
	serial.insert(serial.end(), indexBytes.begin(), indexBytes.end());

	return serial;
}