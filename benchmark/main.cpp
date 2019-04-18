#include "main.hpp"

// System includes
#include <chrono>
#include <iomanip>
#include <iostream>

// Library includes
#include <cryptopp/eccrypto.h>
#include <cryptopp/keccak.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>

// Project includes
#include "common/utxo.hpp"
#include "crypto/signature.hpp"

using namespace ech;

int main()
{
	std::cout << "Signing..." << std::endl;

	CryptoPP::AutoSeededRandomPool prng;

	auto start = std::chrono::high_resolution_clock::now();

	for (auto i = size_t(0); i < 1000u; i++) {
		auto secretKeyInt = CryptoPP::Integer(prng, 256);
		std::stringstream buf;
		buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(secretKeyInt, 16u);
		auto secretKey = crypto::SecretKey(buf.str());

		auto msg = std::string("The quick brown fox jumps over the lazy dog.");
		auto signature = crypto::Signature(msg, secretKey);

		auto publicKey = crypto::PublicKey(secretKey);
		auto result = signature.verify(msg, publicKey);
	}

	auto finish = std::chrono::high_resolution_clock::now();
	auto delta = std::chrono::duration_cast<std::chrono::seconds>(finish - start).count();

	std::cout << "Complete in " << delta << "s." << std::endl;

	return 0;
}