/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_ECH_ETHCLIENTSTUB_H_
#define JSONRPC_CPP_STUB_ECH_ETHCLIENTSTUB_H_

#include <jsonrpccpp/client.h>

namespace ech {
    class EthClientStub : public jsonrpc::Client
    {
        public:
            EthClientStub(jsonrpc::IClientConnector &conn, jsonrpc::clientVersion_t type = jsonrpc::JSONRPC_CLIENT_V2) : jsonrpc::Client(conn, type) {}

            std::string eth_blockNumber() throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p = Json::nullValue;
                Json::Value result = this->CallMethod("eth_blockNumber",p);
                if (result.isString())
                    return result.asString();
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            Json::Value eth_sign(const Json::Value& param1) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                Json::Value result = this->CallMethod("eth_sign",p);
                if (result.isObject())
                    return result;
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            std::string eth_sendTransaction(const Json::Value& param1) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                Json::Value result = this->CallMethod("eth_sendTransaction",p);
                if (result.isString())
                    return result.asString();
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            Json::Value eth_getBlockByHash(const std::string& param1, bool param2) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                p.append(param2);
                Json::Value result = this->CallMethod("eth_getBlockByHash",p);
                if (result.isObject())
                    return result;
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            Json::Value eth_getBlockByNumber(const std::string& param1, bool param2) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                p.append(param2);
                Json::Value result = this->CallMethod("eth_getBlockByNumber",p);
                if (result.isObject())
                    return result;
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            Json::Value eth_getTransactionByHash(const std::string& param1) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                Json::Value result = this->CallMethod("eth_getTransactionByHash",p);
                if (result.isObject())
                    return result;
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            Json::Value eth_getTransactionByBlockHashAndIndex(const std::string& param1, const std::string& param2) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                p.append(param2);
                Json::Value result = this->CallMethod("eth_getTransactionByBlockHashAndIndex",p);
                if (result.isObject())
                    return result;
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            Json::Value eth_getTransactionByBlockNumberAndIndex(const std::string& param1, const std::string& param2) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                p.append(param2);
                Json::Value result = this->CallMethod("eth_getTransactionByBlockNumberAndIndex",p);
                if (result.isObject())
                    return result;
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            Json::Value eth_getTransactionReceipt(const std::string& param1) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                Json::Value result = this->CallMethod("eth_getTransactionReceipt",p);
                if (result.isObject())
                    return result;
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            std::string eth_newFilter(const Json::Value& param1) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                Json::Value result = this->CallMethod("eth_newFilter",p);
                if (result.isString())
                    return result.asString();
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            std::string eth_newBlockFilter() throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p = Json::nullValue;
                Json::Value result = this->CallMethod("eth_newBlockFilter",p);
                if (result.isString())
                    return result.asString();
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            bool eth_uninstallFilter(const std::string& param1) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                Json::Value result = this->CallMethod("eth_uninstallFilter",p);
                if (result.isBool())
                    return result.asBool();
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            Json::Value eth_getFilterChanges(const std::string& param1) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                Json::Value result = this->CallMethod("eth_getFilterChanges",p);
                if (result.isArray())
                    return result;
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            Json::Value eth_getFilterLogs(const std::string& param1) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                Json::Value result = this->CallMethod("eth_getFilterLogs",p);
                if (result.isArray())
                    return result;
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
            Json::Value eth_getLogs(const Json::Value& param1) throw (jsonrpc::JsonRpcException)
            {
                Json::Value p;
                p.append(param1);
                Json::Value result = this->CallMethod("eth_getLogs",p);
                if (result.isArray())
                    return result;
                else
                    throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
            }
    };

}
#endif //JSONRPC_CPP_STUB_ECH_ETHCLIENTSTUB_H_
