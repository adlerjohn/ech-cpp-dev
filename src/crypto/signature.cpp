#include "signature.hpp"

// System includes
#include <iomanip>

// Library includes
#include <secp256k1_recovery.h>

using namespace ech::crypto;

const auto Signature::getContextSign()
{
	static auto context = std::unique_ptr<secp256k1_context, decltype(&secp256k1_context_destroy)>(secp256k1_context_create(SECP256K1_CONTEXT_SIGN), &secp256k1_context_destroy);
	return context.get();
}

const auto Signature::getContextVerify()
{
	static auto context = std::unique_ptr<secp256k1_context, decltype(&secp256k1_context_destroy)>(secp256k1_context_create(SECP256K1_CONTEXT_VERIFY), &secp256k1_context_destroy);
	return context.get();
}

const auto Signature::sign(const SecretKey& secretKey, const Digest& digest)
{
	const auto context = getContextSign();

	secp256k1_ecdsa_recoverable_signature sig;
	if (!secp256k1_ecdsa_sign_recoverable(context, &sig, reinterpret_cast<const unsigned char*>(digest.raw()), reinterpret_cast<const unsigned char*>(secretKey.raw()), nullptr, nullptr))
		throw std::runtime_error("Could not sign message digest: " + digest.toHex());

	std::array<std::byte, 64u> rs;
	int v = 0;
	secp256k1_ecdsa_recoverable_signature_serialize_compact(context, reinterpret_cast<unsigned char *>(rs.data()), &v, &sig);
	v += 27;

	std::stringstream buf;
	buf << std::hex << std::setfill('0');
	for (const auto& c : rs)
		buf << std::setw(2) << static_cast<int>(c);
	buf << std::setw(2) << v;

	return buf.str();
}

Signature::Signature(const std::string& sig)
	: ByteSet(sig)
{
}

Signature::Signature(const SecretKey& secretKey, const std::vector<std::byte>& msg)
	: Signature(sign(secretKey, Digest(msg)))
{
}

Signature::Signature(const SecretKey& secretKey, const std::string& msg)
	: Signature(sign(secretKey, Digest(msg)))
{
}

const PublicKey Signature::recover(const Digest& digest) const
{
	const auto context = getContextVerify();

	const auto v_hex = this->toHex().substr(128, 2);
	std::stringstream buf;
	buf << std::hex << v_hex;
	int v;
	buf >> v;
	v -= 27;

	secp256k1_ecdsa_recoverable_signature sig;
	if (!secp256k1_ecdsa_recoverable_signature_parse_compact(context, &sig, reinterpret_cast<const unsigned char*>(this->raw()), v))
		throw std::runtime_error("Could not parse signature: " + this->toHex());

	secp256k1_pubkey pubkey;
	if (!secp256k1_ecdsa_recover(context, &pubkey, &sig, reinterpret_cast<const unsigned char*>(digest.raw())))
		throw std::runtime_error("Could recover pubkey from signature: " + this->toHex());

	std::array<std::byte, 65u> pubkey_serialized;
	auto outputlen = pubkey_serialized.size();
	secp256k1_ec_pubkey_serialize(context, reinterpret_cast<unsigned char*>(pubkey_serialized.data()), &outputlen, &pubkey, SECP256K1_EC_UNCOMPRESSED);

	std::stringstream buf_pubkey;
	buf_pubkey << std::hex << std::setfill('0');
	auto it = pubkey_serialized.begin();
	for (++it; it != pubkey_serialized.end(); ++it)
		buf_pubkey << std::setw(2) << static_cast<int>(*it);

	return PublicKey(buf_pubkey.str());
}

const bool Signature::verify(const Digest& digest, const Address& address) const
{
	return Address(recover(digest)) == address;
}