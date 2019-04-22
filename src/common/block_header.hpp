#pragma once

// Project includes
#include "crypto/digest.hpp"
#include "serializable.hpp"

namespace ech
{

class BlockHeader : public Serializable
{
private:
	const crypto::Digest _id;
	const uint32_t _version;
	const crypto::Digest _prev;
	const crypto::Digest _root;
	const uint64_t _height;

	[[nodiscard]] const std::vector<std::byte> serializeData(const uint32_t version, const crypto::Digest& prev, const crypto::Digest& root, const uint64_t height) const;

public:
	BlockHeader(const uint32_t version, const crypto::Digest& prev, const crypto::Digest& root, const uint64_t height);

	[[nodiscard]] const auto getVersion() const { return this->_version; }
	[[nodiscard]] const auto getPreviousBlockHash() const { return this->_prev; }
	[[nodiscard]] const auto getId() const { return this->_id; };
	[[nodiscard]] const auto getRoot() const { return this->_root; }
	[[nodiscard]] const auto getHeight() const { return this->_height; };

	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech