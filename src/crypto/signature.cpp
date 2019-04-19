#include "signature.hpp"

// System includes
#include <iomanip>

// Library includes
#include <secp256k1_recovery.h>

using namespace ech::crypto;

const secp256k1_context* Signature::getContextSign()
{
	static std::unique_ptr<secp256k1_context, decltype(&secp256k1_context_destroy)> context(secp256k1_context_create(SECP256K1_CONTEXT_SIGN), &secp256k1_context_destroy);
	return context.get();
}

const secp256k1_context* Signature::getContextVerify()
{
	static std::unique_ptr<secp256k1_context, decltype(&secp256k1_context_destroy)> context(secp256k1_context_create(SECP256K1_CONTEXT_VERIFY), &secp256k1_context_destroy);
	return context.get();
}

auto Signature::sign(const SecretKey& secretKey, const std::string& msg) const
{
	const auto context = getContextSign();

	const auto digest = Digest(msg);
	secp256k1_ecdsa_recoverable_signature sig;
	if (!secp256k1_ecdsa_sign_recoverable(context, &sig, reinterpret_cast<const unsigned char*>(digest.data().data()), reinterpret_cast<const unsigned char*>(secretKey.data().data()), nullptr, nullptr))
		throw std::runtime_error("Could not sign message: " + msg);

	std::array<std::byte, 64u> rs;
	int v = 0;
	secp256k1_ecdsa_recoverable_signature_serialize_compact(context, reinterpret_cast<unsigned char *>(rs.data()), &v, &sig);
	v += 27;

	std::stringstream buf;
	buf << std::hex << std::setfill('0');
	for (auto c : rs)
		buf << std::setw(2) << static_cast<int>(c);
	buf << std::setw(2) << v;

	return buf.str();
}

Signature::Signature(const std::string& sig)
	: ByteSet(sig)
{
}

Signature::Signature(const SecretKey& secretKey, const std::string& str)
	: Signature(sign(secretKey, str))
{
}

PublicKey Signature::recover(const std::string& msg) const
{
	const auto context = getContextVerify();

	const auto v_hex = this->toHex().substr(128, 2);
	std::stringstream buf;
	buf << std::hex << v_hex;
	int v;
	buf >> v;
	v -= 27;

	const auto digest = Digest(msg);
	secp256k1_ecdsa_recoverable_signature sig;
	if (!secp256k1_ecdsa_recoverable_signature_parse_compact(context, &sig, reinterpret_cast<const unsigned char*>(this->data().data()), v))
		throw std::runtime_error("Could not parse signature: " + this->toHex());

	secp256k1_pubkey pubkey;
	if (!secp256k1_ecdsa_recover(context, &pubkey, &sig, reinterpret_cast<const unsigned char*>(digest.data().data())))
		throw std::runtime_error("Could recover pubkey from signature: " + this->toHex());

	std::array<std::byte, 65u> pubkey_serialized;
	size_t outputlen = pubkey_serialized.size();
	secp256k1_ec_pubkey_serialize(context, reinterpret_cast<unsigned char*>(pubkey_serialized.data()), &outputlen, &pubkey, SECP256K1_EC_UNCOMPRESSED);

	std::stringstream buf_pubkey;
	buf_pubkey << std::hex << std::setfill('0');
	auto it = pubkey_serialized.begin();
	for (++it; it != pubkey_serialized.end(); ++it)
		buf_pubkey << std::setw(2) << static_cast<int>(*it);

	return PublicKey(buf_pubkey.str());
}

bool Signature::verify(const std::string& msg, const Address& address) const
{
	return Address(recover(msg)) == address;
}

bool Signature::verify(const std::string& msg, const PublicKey& publicKey) const
{
	return verify(msg, Address(publicKey));
}