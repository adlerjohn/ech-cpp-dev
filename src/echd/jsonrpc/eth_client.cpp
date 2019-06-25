#include "eth_client.hpp"

// Library includes
#include <jsonrpccpp/client/connectors/httpclient.h>

// Project includes
#include "eth_client_stub.hpp"

using namespace ech;

eth::Filter::Filter(
	const std::optional<uint64_t>& fromBlock,
	const std::optional<uint64_t>& toBlock,
	const std::optional<crypto::Address>& address,
	const std::vector<std::pair<std::string, std::string>>& topics,
	const std::optional<crypto::Digest>& blockHash)
	: _fromBlock(fromBlock)
	, _toBlock(toBlock)
	, _address(address)
	, _topics(topics)
	, _blockHash(blockHash)
{
}

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

const std::string eth::JsonHelper::toString(const uint64_t number)
{
	std::stringstream buf;
	buf << std::hex << std::setfill('0') << std::setw(8u * 2) << number;
	auto str = buf.str();
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	return formatHex(removeLeadingZeroes(str));
}

const Json::Value eth::JsonHelper::toValue(const uint64_t number)
{
	const auto val = Json::Value(toString(number));
	return val;
}

const std::string eth::JsonHelper::toString(const crypto::Digest& hash)
{
	return formatHex(hash.toHex());
}

const Json::Value eth::JsonHelper::toValue(const crypto::Digest& hash)
{
	const auto val = Json::Value(toString(hash));
	return val;
}

const Json::Value eth::JsonHelper::toValue(const crypto::Address& address)
{
	const auto val = Json::Value(formatHex(address.toHex()));
	return val;
}

const Json::Value eth::JsonHelper::toValue(const eth::Filter& filter)
{
	auto val = Json::Value(Json::objectValue);

	if (const auto& fromBlock = filter.getFromBlock(); fromBlock) {
		val["fromBlock"] = toValue(fromBlock.value());
	}
	if (const auto& toBlock = filter.getToBlock(); toBlock) {
		val["toBlock"] = toValue(toBlock.value());
	}
	if (const auto& address = filter.getAddress(); address) {
		val["address"] = toValue(address.value());
	}
	const auto& topics = filter.getTopics();
	val["topics"] = Json::Value(Json::arrayValue);
	for (const auto& topic: topics) {
		//val["topics"].append(TODO);
	}
	if (const auto& blockHash = filter.getBlockHash(); blockHash) {
		val["blockHash"] = toValue(blockHash.value());
	}

	return val;
}

EthClient::EthClient()
	: _httpClient(jsonrpc::HttpClient("http://localhost:8545"))
	, _clientStub(EthClientStub(_httpClient, jsonrpc::JSONRPC_CLIENT_V2))
{
}

const std::string EthClient::eth_blockNumber()
{
	return _clientStub.eth_blockNumber();
}

const Json::Value EthClient::eth_sign(const std::string& data)
{
	// TODO
	return Json::Value();
}

const std::string EthClient::eth_sendTransaction(const eth::Transaction& tx)
{
	// TODO
	return std::__cxx11::string();
}

const Json::Value EthClient::eth_getBlockByNumber(const uint64_t number, bool isFullTransactionObjects)
{
	return _clientStub.eth_getBlockByNumber(eth::JsonHelper::toString(number), isFullTransactionObjects);
}

const Json::Value EthClient::eth_getTransactionByHash(const crypto::Digest& hash)
{
	return _clientStub.eth_getTransactionByHash(eth::JsonHelper::toString(hash));
}

const std::string EthClient::eth_newFilter(const eth::Filter& filterObject)
{
	return _clientStub.eth_newFilter(eth::JsonHelper::toValue(filterObject));
}

const std::string EthClient::eth_newBlockFilter()
{
	return _clientStub.eth_newBlockFilter();
}

const bool EthClient::eth_uninstallFilter(const std::string& filterID)
{
	// TODO
	return 0;
}

const Json::Value EthClient::eth_getFilterChanges(const std::string& filterID)
{
	// TODO
	return Json::Value();
}

const Json::Value EthClient::eth_getFilterLogs(const std::string& filterID)
{
	// TODO
	return Json::Value();
}

const Json::Value EthClient::eth_getLogs(const eth::Filter& filterObject)
{
	return _clientStub.eth_getLogs(eth::JsonHelper::toValue(filterObject));
}