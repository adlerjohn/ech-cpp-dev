#pragma once

// System includes
#include <vector>

// Project includes
#include "bench.hpp"
#include "crypto/signature.hpp"

namespace ech::benchmark
{

class SigningData
{
private:
	const crypto::SecretKey _secretKey;
	const crypto::PublicKey _publicKey;
	const std::string _msg;
	const crypto::Signature _signature;
public:
	SigningData(const crypto::SecretKey& secretKey, const std::string& msg, const crypto::Signature& signature);

	auto getSecretKey() const { return _secretKey; }

	auto getPublicKey() const { return _publicKey; }

	auto getMsg() const { return _msg; }

	auto getSignature() const { return _signature; }
};

class Signing : public Benchmark
{
private:
	std::vector<SigningData> _data;
public:
	void setup() override;
	void run() override;

	void run(const crypto::Signer& signer);
};

} // namespace ech::benchmark