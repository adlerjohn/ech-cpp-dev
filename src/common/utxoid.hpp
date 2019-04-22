#pragma once

// Project includes
#include "crypto/digest.hpp"
#include "outpoint.hpp"

namespace ech
{

//using UTXOID = crypto::Digest;

class UTXOID : public crypto::Digest
{
public:
	explicit UTXOID(const Outpoint& outpoint);
};

} // namespace ech