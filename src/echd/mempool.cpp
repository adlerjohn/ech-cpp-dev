#include "mempool.hpp"

using namespace ech;

void Mempool::add(const TX& tx)
{
	_pending.emplace(tx.getData().getId(), std::make_unique<TX>(tx));
}

void Mempool::remove(const TXID& txid)
{
	const auto& pos = _pending.find(txid);

	if (pos == _pending.end()) {
		throw std::runtime_error("tx not found in mempool");
	}

	_pending.erase(pos);
}
const bool Mempool::exists(const TXID& txid) const
{
	return (_pending.find(txid) != _pending.end());
}

const std::unique_ptr<TX>& Mempool::find(const TXID& txid) const
{
	// TODO add some sanity check here
	return _pending.find(txid)->second;
}
