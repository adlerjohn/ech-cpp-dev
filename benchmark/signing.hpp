#pragma once

// System includes
#include <thread>
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
	static constexpr uint64_t _count = 100000u;
	std::atomic<uint64_t> _passed{0};
	std::vector<SigningData> _data;

	void runThread(const size_t begin, const size_t size);

public:
	void setup() override;

	void run() override;

	void run(const uint64_t threadCount);

	[[nodiscard]] static constexpr auto count() { return _count; }

	void reset() { _passed = 0u; }
};

} // namespace ech::benchmark