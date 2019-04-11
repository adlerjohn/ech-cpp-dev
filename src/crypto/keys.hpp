#pragma once

// Library includes
#include <crypto++/eccrypto.h>
#include <crypto++/oids.h>
#include <crypto++/osrng.h>

namespace ech
{
namespace crypto
{

using PublicKey = CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey;

} // namespace crypto
} // namespace ech