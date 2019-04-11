#include "digest.hpp"

// Library includes
#include <crypto++/cryptlib.h>
#include <crypto++/filters.h>
#include <crypto++/hex.h>
#include <crypto++/keccak.h>

using namespace ech::crypto;

auto Digest::hash(const std::string& str)
{
	CryptoPP::Keccak_256 hash;
	hash.Update((const byte*)str.data(), str.size());

	auto digest = std::string(digestBytes(), '0');
	hash.Final((byte*)&digest[0]);

	std::string hexDigest;
	CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hexDigest), false);
	CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));

	return DigestData(hexDigest);
}

Digest::Digest(const std::string& str, bool isDigest)
	: _data(hash(str))
{
}

Digest::Digest(const std::string& str)
	: Digest(str, false)
{
}
