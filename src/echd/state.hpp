#pragma once

// System includes
#include <map>
#include <vector>

// Project includes
#include "common/utxo.hpp"

namespace ech
{

class State : public Serializable
{
private:
	// TODO use rocksdb for this
	// The UTXO set: blockchain state
	std::map<UTXOID, std::unique_ptr<UTXO>> _utxoSet;

public:
	[[nodiscard]] static const State deserialize(std::deque<std::byte>& serial);

	void add(const std::vector<UTXO>& utxos);

	void remove(const std::vector<UTXOID>& utxoids);

	[[nodiscard]] const bool exists(const UTXOID& utxoid) const;
	[[nodiscard]] const std::unique_ptr<UTXO>& find(const UTXOID& utxoid) const;

	[[nodiscard]] const auto& data() const { return this->_utxoSet; }
	[[nodiscard]] const auto size() const { return this->_utxoSet.size(); }

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech