#include "state.hpp"

// Project includes
#include "common/deserializer.hpp"
#include "common/serializer.hpp"

using namespace ech;

const State State::deserialize(std::deque<std::byte>& serial)
{
	State state;

	const auto stateSize = deserializer::deserialize<uint64_t, 8u>(serial);
	for (size_t i = 0; i < stateSize; i++) {
		state.add({UTXO::deserialize(serial)});
	}

	return state;
}

void State::add(const std::vector<UTXO>& utxos)
{
	for (const auto& utxo : utxos) {
		_utxoSet.insert({utxo.getId(), utxo});
	}
}

void State::remove(const std::vector<UTXO>& utxos)
{
	for (const auto& utxo : utxos) {
		const auto& pos = _utxoSet.find(utxo.getId());

		if (pos == _utxoSet.end()) {
			throw std::runtime_error("utxo not found");
		}

		_utxoSet.erase(pos);
	}
}

const bool State::exists(const UTXOID& utxoid) const
{
	return (_utxoSet.find(utxoid) != _utxoSet.end());
}

const UTXO& State::find(const UTXOID& utxoid) const
{
	// TODO add some sanity check here
	return _utxoSet.find(utxoid)->second;
}

const std::vector<std::byte> State::serialize() const
{
	std::vector<std::byte> serial;

	const uint64_t stateSize = _utxoSet.size();
	const auto stateSizeBytes = serializer::serialize<uint64_t, 8u>(stateSize);
	serial.insert(serial.end(), stateSizeBytes.begin(), stateSizeBytes.end());

	for (const auto& kv : _utxoSet) {
		const auto utxoBytes = kv.second.serialize();
		serial.insert(serial.end(), utxoBytes.begin(), utxoBytes.end());
	}
	return serial;
}