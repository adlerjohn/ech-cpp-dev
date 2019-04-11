#pragma once

// Library includes
#include <crypto++/eccrypto.h>
#include <crypto++/oids.h>
#include <crypto++/osrng.h>

namespace ech::crypto
{

using PublicKey = CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey;
using SecretKey = CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey;

} // namespace ech::crypto