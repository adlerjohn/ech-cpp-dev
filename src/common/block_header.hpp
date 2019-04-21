#pragma once

// Project includes
#include "serializable.hpp"
#include "crypto/digest.hpp"

namespace ech
{

class BlockHeader : public Serializable
{
private:
	const crypto::Digest _id;
	const crypto::Digest _root;
	const uint64_t _height;

public:
	BlockHeader(const crypto::Digest& root, const uint64_t height);

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech