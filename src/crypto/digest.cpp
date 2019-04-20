#include "digest.hpp"

// Library includes
#include <cryptopp/keccak.h>

using namespace ech::crypto;

const auto Digest::hash(const std::string& str) const
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

const Digest Digest::concat(const Digest& rhs) const
{
	constexpr auto size2 = size() * 2u;

	std::array<std::byte, size2> concatenated;
	CryptoPP::StringSource(this->toHex() + rhs.toHex(), true,
		new CryptoPP::HexDecoder(
			new CryptoPP::ArraySink(reinterpret_cast<CryptoPP::byte*>(concatenated.data()), size2)
		)
	);

	CryptoPP::Keccak_256 hash;
	std::string digest;
	CryptoPP::ArraySource(reinterpret_cast<const CryptoPP::byte*>(concatenated.data()), size2, true,
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

	return Digest(hexDigest, true);
}

Digest::Digest(const std::string& str, const bool isDigest)
	: ByteSet(isDigest ? str : hash(str))
{
}