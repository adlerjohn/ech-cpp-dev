#pragma once

// Project includes
#include "crypto/digest.hpp"
#include "outpoint.hpp"

namespace ech
{

class UTXOID : public crypto::Digest
{
public:
	explicit UTXOID(const std::array<std::byte, UTXOID::size()>& bytes);

	explicit UTXOID(const Outpoint& outpoint);
};

} // namespace ech