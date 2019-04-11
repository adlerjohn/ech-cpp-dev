#pragma once

// Project includes
#include "byteset.hpp"

#define DIGEST_BYTES 32u

namespace ech::crypto
{

class Digest : public byteset<DIGEST_BYTES>
{
private:
	auto hash(const std::string& str);
public:
	explicit Digest(const std::string& str, bool isDigest);
	explicit Digest(const std::string& str);
};

} // namespace ech::crypto