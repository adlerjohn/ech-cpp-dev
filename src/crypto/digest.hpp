#pragma once

// Project includes
#include "byteset.hpp"

#define DIGEST_BYTES 32u

namespace ech::crypto
{

class Digest : public byteset<DIGEST_BYTES>
{
private:
	[[nodiscard]] const auto hash(const std::string& msg) const;

	[[nodiscard]] const auto hash(const std::vector<std::byte>& bytes) const;

	[[nodiscard]] const Digest concat(const Digest& rhs) const;

public:
	explicit Digest(const std::string& msg, bool isDigest = false);

	explicit Digest(const std::vector<std::byte>& bytes);

	friend const auto operator+(const Digest& lhs, const Digest& rhs) {
		return lhs.concat(rhs);
	}
};

} // namespace ech::crypto