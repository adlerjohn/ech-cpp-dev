#include "digest.hpp"

// Library includes
#include <cryptopp/keccak.h>

using namespace ech::crypto;

const auto Digest::hash(const std::string& msg) const
{
	CryptoPP::Keccak_256 hash;

	std::array<CryptoPP::byte, size()> digest;
	CryptoPP::StringSource(msg, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::ArraySink(digest.data(), size()),
			false, size()
		)
	);

	std::string hexDigest;
	CryptoPP::ArraySource(digest.data(), size(), true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(hexDigest),
			false
		)
	);

	return hexDigest;
}

const auto Digest::hash(const std::vector<std::byte>& bytes) const
{
	CryptoPP::Keccak_256 hash;

	std::array<CryptoPP::byte, size()> digest;
	CryptoPP::ArraySource(reinterpret_cast<const CryptoPP::byte*>(bytes.data()), bytes.size(), true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::ArraySink(digest.data(), size()),
			false, size()
		)
	);

	std::string hexDigest;
	CryptoPP::ArraySource(digest.data(), size(), true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(hexDigest),
			false
		)
	);

	return hexDigest;
}

const Digest Digest::concat(const Digest& rhs) const
{
	const auto& lhs = *this;

	std::vector<std::byte> bytes;
	bytes.insert(bytes.end(), lhs.begin(), lhs.end());
	bytes.insert(bytes.end(), rhs.begin(), rhs.end());

	return Digest(bytes);
}

Digest::Digest()
	: ByteSet("290decd9548b62a8d60345a988386fc84ba6bc95484008f6362f93160ef3e563")
{
}

Digest::Digest(const std::string& msg, const bool isDigest)
	: ByteSet(isDigest ? msg : hash(msg))
{
}

Digest::Digest(const std::vector<std::byte>& bytes)
	: ByteSet(hash(bytes))
{
}