#include "eth_client.hpp"

// Project includes
#include "eth_client_stub.hpp"

using namespace ech;

const std::string eth::JsonHelper::formatHex(const std::string& val)
{
	return std::string("0x") + val;
}

const std::string eth::JsonHelper::removeLeadingZeroes(const std::string& val)
{
	std::string s;

	if (!val.empty()) {
		// Remove all leading zeroes
		size_t offset = 0;
		const auto len = val.length();
		while (offset < len && val.at(offset) == '0') {
			offset++;
		}
		s = val.substr(offset);
	}

	if (s.empty()) {
		// Special case: zero is encoded is 0x0
		s = std::string_view("0");
	}

	return s;
}

const Json::Value eth::JsonHelper::toValue(const uint64_t number)
{
	auto val = Json::Value(Json::stringValue);
	return val;
}

const Json::Value eth::JsonHelper::toValue(const crypto::Digest& hash)
{
	auto val = Json::Value(Json::stringValue);
	return val;
}

const Json::Value eth::JsonHelper::toValue(const eth::Filter& filter)
{
	auto val = Json::Value(Json::objectValue);
	return val;
}

EthClient::EthClient()
{
}

const std::string EthClient::eth_blockNumber() const
{
	return std::__cxx11::string();
}

const Json::Value EthClient::eth_sign(const std::string& data) const
{
	return Json::Value();
}

const std::string EthClient::eth_sendTransaction(const eth::Transaction& tx) const
{
	return std::__cxx11::string();
}

const Json::Value EthClient::eth_getBlockByNumber(const uint64_t number, bool isFullTransactionObjects) const
{
	return Json::Value();
}
const Json::Value EthClient::eth_getTransactionByHash(const crypto::Digest& hash) const
{
	return Json::Value();
}

const std::string EthClient::eth_newFilter(const eth::Filter& filterObject) const
{
	return std::__cxx11::string();
}

const std::string EthClient::eth_newBlockFilter() const
{
	return std::__cxx11::string();
}

const bool EthClient::eth_uninstallFilter(const std::string& filterID) const
{
	return 0;
}

const Json::Value EthClient::eth_getFilterChanges(const std::string& filterID) const
{
	return Json::Value();
}

const Json::Value EthClient::eth_getFilterLogs(const std::string& filterID) const
{
	return Json::Value();
}

const Json::Value EthClient::eth_getLogs(const eth::Filter& filterObject) const
{
	return Json::Value();
}