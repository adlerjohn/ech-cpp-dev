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

void Signing::setup()
{
	CryptoPP::AutoSeededRandomPool prng;

	for (auto i = size_t(0); i < 5000u; i++) {
		auto secretKeyInt = CryptoPP::Integer(prng, 256);
		std::stringstream buf;
		buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(secretKeyInt, 16u);
		auto secretKey = crypto::SecretKey(buf.str());

		auto msg = std::string("The quick brown fox jumps over the lazy dog.");
		auto signature = crypto::Signature(msg, secretKey);

		this->_data.emplace_back(SigningData(secretKey, msg, signature));
	}
}

void Signing::run()
{
	this->before();

	for (auto& d : this->_data) {
		d.getSignature().verify(d.getMsg(), d.getPublicKey());
	}

	this->after();
}