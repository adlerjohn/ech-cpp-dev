#include "state.hpp"

using namespace ech;

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