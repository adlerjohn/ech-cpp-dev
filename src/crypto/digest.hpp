#pragma once

// Project includes
#include "byteset.hpp"

#define DIGEST_BYTES 32u

namespace ech::crypto
{

class Digest : public byteset<DIGEST_BYTES>
{
private:
	[[nodiscard]] const auto hash(const std::string& str) const;

	[[nodiscard]] const Digest concat(const Digest& rhs) const;

public:
	explicit Digest(const std::string& str, bool isDigest = false);

	friend const auto operator+(const Digest& lhs, const Digest& rhs) {
		return lhs.concat(rhs);
	}
};

} // namespace ech::crypto