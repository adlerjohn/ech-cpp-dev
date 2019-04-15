#pragma once

// System includes
#include <string>

// Project includes
#include "byteset.hpp"
#include "digest.hpp"

#define SECRET_KEY_BYTES 32u
#define PUBLIC_KEY_BYTES 64u

namespace ech::crypto
{

class SecretKey : public byteset<SECRET_KEY_BYTES>
{
public:
	explicit SecretKey(const std::string& str);

	std::string sign(const Digest& msg) const;

	std::string sign(const std::string& str) const;
};

class PublicKey : public byteset<PUBLIC_KEY_BYTES>
{
private:
	static auto deriveFromSecretKey(const SecretKey& secretKey);

	static auto deterministicK(const Digest& msg, const SecretKey& secretKey);

	static auto deterministicK(const std::string& str, const SecretKey& secretKey);

public:
	explicit PublicKey(const std::string& str);

	explicit PublicKey(const SecretKey& secretKey);
};

} // namespace ech::crypto