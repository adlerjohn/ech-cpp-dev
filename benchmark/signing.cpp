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

void Signing::run()
{
	this->before();

	CryptoPP::AutoSeededRandomPool prng;

	for (auto i = size_t(0); i < 100u; i++) {
		auto secretKeyInt = CryptoPP::Integer(prng, 256);
		std::stringstream buf;
		buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(secretKeyInt, 16u);
		auto secretKey = crypto::SecretKey(buf.str());

		auto msg = std::string("The quick brown fox jumps over the lazy dog.");
		auto signature = crypto::Signature(msg, secretKey);

		auto publicKey = crypto::PublicKey(secretKey);
		auto result = signature.verify(msg, publicKey);
	}

	this->after();
}