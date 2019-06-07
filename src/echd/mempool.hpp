#pragma once

// System includes
#include <map>

// Project includes
#include "common/tx.hpp"
#include "common/txid.hpp"

namespace ech
{

class Mempool
{
private:
	std::map<TXID, std::unique_ptr<TX>> _pending;

public:
	void add(const TX& tx);

	void remove(const TXID& txid);

	[[nodiscard]] const bool exists(const TXID& txid) const;
	[[nodiscard]] const std::unique_ptr<TX>& find(const TXID& txid) const;
};

} // namespace ech
