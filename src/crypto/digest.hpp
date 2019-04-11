#pragma once

// Project includes
#include "byteset.hpp"

#define DIGEST_BYTES 32u

namespace ech::crypto
{

using DigestData = byteset<DIGEST_BYTES>;

class Digest
{
private:
	const DigestData _data;

	auto hash(const std::string& str);
public:
	explicit Digest(const std::string& str, bool isDigest);
	explicit Digest(const std::string& str);

	static auto digestBytes() { return DIGEST_BYTES; }

	auto data() const { return this->_data; }
};

} // namespace ech::crypto