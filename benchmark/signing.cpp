#include "signing.hpp"

// System includes
#include <iomanip>

// Library includes
#include <cryptopp/eccrypto.h>
#include <cryptopp/keccak.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>

// Project includes
#include "crypto/signature.hpp"

using namespace ech::benchmark;

SigningData::SigningData(const crypto::SecretKey& secretKey, const std::string& msg, const crypto::Signature& signature)
	: _secretKey(secretKey)
	, _publicKey(crypto::PublicKey(secretKey))
	, _msg(msg)
	, _signature(signature)
{
}

void Signing::runThread(const size_t begin, const size_t size)
{
	uint64_t passed = 0;

	for (size_t i = begin; i < begin+size; i++) {
		const auto& d = _data.at(i);
		const auto result = d.getSignature().verify(d.getMsg(), d.getPublicKey());
		if (result)
			passed++;
	}

	this->_passed += passed;
}

void Signing::setup()
{
	CryptoPP::AutoSeededRandomPool prng;

	for (auto i = size_t(0); i < Signing::count(); i++) {
		auto secretKeyInt = CryptoPP::Integer(prng, 256);
		std::stringstream buf;
		buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(secretKeyInt, 16u);
		auto secretKey = crypto::SecretKey(buf.str());

		auto msg = std::string("The quick brown fox jumps over the lazy dog.");
		auto signature = crypto::Signature(secretKey, msg);

		this->_data.emplace_back(SigningData(secretKey, msg, signature));
	}
}

void Signing::run()
{
	this->before();

	for (auto& d : this->_data) {
		const auto result = d.getSignature().verify(d.getMsg(), d.getPublicKey());
		if (result)
			this->_passed++;
	}

	this->after();
}

void Signing::run(const uint64_t threadCount)
{
	this->before();

	const auto offset = Signing::count() / threadCount;

	std::vector<std::thread> threads;

	for (size_t i = 0; i < Signing::count(); i += offset) {
		threads.push_back(std::thread(&Signing::runThread, this, i, offset));
	}

	for (auto& t : threads)
		t.join();

	this->after();
}