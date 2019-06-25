#pragma once

// Project includes
#include "crypto/digest.hpp"
#include "eth_client_stub.hpp"
#include <crypto/address.hpp>

namespace ech
{

namespace eth
{

class Transaction
{
private:
public:
};

class Filter
{
private:
	std::optional<uint64_t> _fromBlock;
	std::optional<uint64_t> _toBlock;
	std::optional<crypto::Address> _address;
	std::vector<std::pair<std::string, std::string>> _topics;
	std::optional<crypto::Digest> _blockHash;

public:
	Filter(
		const std::optional<uint64_t>& fromBlock,
		const std::optional<uint64_t>& toBlock,
		const std::optional<crypto::Address>& address,
		const std::vector<std::pair<std::string, std::string>>& topics,
		const std::optional<crypto::Digest>& blockHash);

	[[nodiscard]] const auto& getFromBlock() const { return _fromBlock; }
	[[nodiscard]] const auto& getToBlock() const { return _toBlock; }
	[[nodiscard]] const auto& getAddress() const { return _address; }
	[[nodiscard]] const auto& getTopics() const { return _topics; }
	[[nodiscard]] const auto& getBlockHash() const { return _blockHash; }
};

class JsonHelper
{
public:
	// https://github.com/ethereum/wiki/wiki/JSON-RPC#hex-value-encoding
	[[nodiscard]] static const std::string formatHex(const std::string& val);
	[[nodiscard]] static const std::string removeLeadingZeroes(const std::string& val);

	[[nodiscard]] static const Json::Value toValue(const uint64_t number);
	[[nodiscard]] static const Json::Value toValue(const crypto::Digest& hash);
	[[nodiscard]] static const Json::Value toValue(const crypto::Address& address);
	[[nodiscard]] static const Json::Value toValue(const Filter& filter);
};

} // namespace eth

class EthClient
{
private:
public:
	EthClient();

	[[nodiscard]] const std::string eth_blockNumber() const;
	[[nodiscard]] const Json::Value eth_sign(const std::string& data) const;
	[[nodiscard]] const std::string eth_sendTransaction(const eth::Transaction& tx) const;
	[[nodiscard]] const Json::Value eth_getBlockByNumber(const uint64_t number, bool isFullTransactionObjects) const;
	[[nodiscard]] const Json::Value eth_getTransactionByHash(const crypto::Digest& hash) const;
	[[nodiscard]] const std::string eth_newFilter(const eth::Filter& filterObject) const;
	[[nodiscard]] const std::string eth_newBlockFilter() const;
	[[nodiscard]] const bool eth_uninstallFilter(const std::string& filterID) const;
	[[nodiscard]] const Json::Value eth_getFilterChanges(const std::string& filterID) const;
	[[nodiscard]] const Json::Value eth_getFilterLogs(const std::string& filterID) const;
	[[nodiscard]] const Json::Value eth_getLogs(const eth::Filter& filterObject) const;
};

} // namespace ech