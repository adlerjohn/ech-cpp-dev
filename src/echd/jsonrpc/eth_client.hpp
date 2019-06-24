#pragma once

// Project includes
#include "crypto/digest.hpp"
#include "eth_client_stub.hpp"

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
public:
};

class JsonHelper
{
	[[nodiscard]] static const std::string formatHex(const std::string& val);
	[[nodiscard]] static const std::string removeLeadingZeroes(const std::string& val);

public:
	[[nodiscard]] static const Json::Value toValue(const uint64_t number);
	[[nodiscard]] static const Json::Value toValue(const crypto::Digest hash);
	[[nodiscard]] static const Json::Value toValue(const Filter filter);
};

} // namespace eth

class EthClient
{
private:
public:
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