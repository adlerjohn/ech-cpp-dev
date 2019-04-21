#include "address.hpp"

// Library includes
#include <cryptopp/cryptlib.h>
#include <cryptopp/keccak.h>

using namespace ech::crypto;

auto Address::toAddress(const PublicKey& publicKey)
{
	CryptoPP::Keccak_256 hash;
	std::string digest;
	CryptoPP::ArraySource(reinterpret_cast<const CryptoPP::byte*>(publicKey.raw()), PublicKey::size(), true,
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

Address::Address()
	: ByteSet(std::string(Address::size() * 2, '0'))
{
}

Address::Address(const std::string& str)
	: ByteSet(str)
{
}

Address::Address(const PublicKey& publicKey)
	: Address(toAddress(publicKey))
{
}