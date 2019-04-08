#pragma once

// Library includes
#include <crypto++/eccrypto.h>
#include <crypto++/osrng.h>
#include <crypto++/oids.h>

#define ADDRESS_BYTES 20

/**
 * Addresses are the last 20 bytes of the Keccak-256 of the hex
 * representation of the public key.
 */
class Address
{
private:
public:
};