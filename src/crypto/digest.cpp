#include "digest.hpp"

// Library includes
#include <cryptopp/cryptlib.h>
#include <cryptopp/keccak.h>

using namespace ech::crypto;

auto Digest::hash(const std::string& str) const
{
	CryptoPP::Keccak_256 hash;
	std::string digest;
	CryptoPP::StringSource(str, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::StringSink(digest),
			false, size()
		)
	);

	std::string hexDigest;
	CryptoPP::StringSource(digest, true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(hexDigest),
			false
		)
	);

	return hexDigest;
}

Digest::Digest(const std::string& str, bool isDigest)
	: ByteSet(isDigest ? str : hash(str))
{
}

Digest::Digest(const std::string& str)
	: Digest(str, false)
{
}
