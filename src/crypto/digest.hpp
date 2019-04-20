#pragma once

// Project includes
#include "byteset.hpp"

#define DIGEST_BYTES 32u

namespace ech::crypto
{

class Digest : public byteset<DIGEST_BYTES>
{
private:
	const auto hash(const std::string& str) const;

public:
	explicit Digest(const std::string& str, bool isHex = false);
};

} // namespace ech::crypto