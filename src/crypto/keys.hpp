#pragma once

// System includes
#include <string>

// Library includes
#include <secp256k1.h>

// Project includes
#include "byteset.hpp"
#include "digest.hpp"

#define SECRET_KEY_BYTES 32u
#define PUBLIC_KEY_BYTES 64u

namespace ech::crypto
{

// TODO need to zero out secret key on destroy
class SecretKey : public byteset<SECRET_KEY_BYTES>
{
public:
	explicit SecretKey(const std::string& str);
};

class PublicKey : public byteset<PUBLIC_KEY_BYTES>
{
private:
	static const secp256k1_context* getContextKeys();

	static auto deriveFromSecretKey(const SecretKey& secretKey);

public:
	explicit PublicKey(const std::string& str);

	explicit PublicKey(const SecretKey& secretKey);
};

} // namespace ech::crypto