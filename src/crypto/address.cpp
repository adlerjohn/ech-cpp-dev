#include "address.hpp"

// Library includes
#include <crypto++/cryptlib.h>
#include <crypto++/filters.h>
#include <crypto++/hex.h>
#include <crypto++/keccak.h>

using namespace ech::crypto;

auto Address::toAddress(const std::string& pk) const
{
	CryptoPP::Keccak_256 hash;
	hash.Update((const byte*)pk.data(), pk.size());

	auto digest = std::string(size(), '0');
	hash.TruncatedFinal((byte*)&digest[0], digest.size());

	std::string hexAddress;
	CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hexAddress), false);
	CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));

	return hexAddress;
}

Address::Address(const std::string& pk)
	: ByteSet(toAddress(pk))
{
}

Address::Address(const PublicKey& pk)
	: Address(pk.toHex())
{
}