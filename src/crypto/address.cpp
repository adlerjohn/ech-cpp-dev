#include "address.hpp"

// Library includes
#include <cryptopp/cryptlib.h>
#include <cryptopp/keccak.h>

using namespace ech::crypto;

auto Address::toAddress(const std::string& publicKey)
{
	std::string decoded;
	CryptoPP::StringSource(publicKey, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decoded)
		)
	);

	CryptoPP::Keccak_256 hash;
	std::string digest;
	CryptoPP::StringSource(decoded, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::StringSink(digest),
			false)
	);
	// Only keep the last 20 bytes
	digest = digest.substr(digest.length() - size());

	std::string hexAddress;
	CryptoPP::StringSource(digest, true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(hexAddress),
			false)
	);

	return hexAddress;
}

Address::Address(const std::string& publicKey)
	: ByteSet(toAddress(publicKey))
{
}

Address::Address(const PublicKey& publicKey)
	: Address(publicKey.toHex())
{
}