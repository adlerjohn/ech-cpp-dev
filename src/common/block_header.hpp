#pragma once

// Project includes
#include "serializable.hpp"

namespace ech
{

class BlockHeader : public Serializable
{
private:
	// TODO id
	// TODO merkle root
	// TODO height
public:
	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech