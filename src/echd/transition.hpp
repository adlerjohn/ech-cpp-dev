#pragma once

// Project includes
#include "common/utxo.hpp"

namespace ech
{

class Transition
{
private:
	const std::vector<UTXO> _add;
	const std::vector<UTXO> _remove;

public:
	Transition(const std::vector<UTXO>& add, const std::vector<UTXO>& remove);

	[[nodiscard]] const auto getAdditions() const { return this->_add; }
	[[nodiscard]] const auto getRemovals() const { return this->_remove; }
};

} // namespace ech