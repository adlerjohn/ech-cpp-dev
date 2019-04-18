#pragma once

// Project includes
#include "signature.hpp"

namespace ech::crypto
{

class Signature;

class Signer
{
public:
	virtual Signature sign(const SecretKey& secretKey, const std::string& msg) const = 0;

	virtual PublicKey recover(const Signature& signature, const std::string& msg) const = 0;

	bool verify(const Signature& signature, const std::string& msg, const Address& address) const;

	bool verify(const Signature& signature, const std::string& msg, const PublicKey& publicKey) const;
};

class Signer_CryptoPP : public Signer
{
public:
	Signature sign(const SecretKey& secretKey, const std::string& msg) const override;

	PublicKey recover(const Signature& signature, const std::string& msg) const override;

	bool verify_direct(const Signature& signature, const std::string& msg, const PublicKey& publicKey) const;
};

class Signer_libsecp256k1 : public Signer
{
public:
	Signature sign(const SecretKey& secretKey, const std::string& msg) const override;

	PublicKey recover(const Signature& signature, const std::string& msg) const override;
};

} // namespace ech::crypto