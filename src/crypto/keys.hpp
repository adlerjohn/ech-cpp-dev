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
};

class PublicKey : public byteset<PUBLIC_KEY_BYTES>
{
private:
	static auto deriveFromSecretKey(const SecretKey& secretKey);

public:
	explicit PublicKey(const std::string& str);

	explicit PublicKey(const SecretKey& secretKey);
};

} // namespace ech::crypto