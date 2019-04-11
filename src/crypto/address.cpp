#include "address.hpp"

// Library includes
#include <crypto++/cryptlib.h>
#include <crypto++/filters.h>
#include <crypto++/hex.h>
#include <crypto++/keccak.h>

using namespace ech::crypto;

auto Address::toAddress(const PublicKey& pk) const
{
	auto hex = pk.toHex();

	CryptoPP::Keccak_256 hash;
	std::string hexAddress;
	CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hexAddress), false);
	auto digest = std::string(addressBytes(), '0');

	hash.Update((const byte*)hex.data(), hex.size());
	hash.TruncatedFinal((byte*)&digest[0], digest.size());
	CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));

	return PublicKeyAddress(hexAddress);
}

auto Address::toAddress(const std::string& pk) const
{
	auto publicKey = PublicKey(pk);
	return toAddress(publicKey);
}

Address::Address(const std::string& pk)
	: _addr(toAddress(pk))
{
}

Address::Address(const PublicKey& pk)
	: _addr(toAddress(pk))
{
}