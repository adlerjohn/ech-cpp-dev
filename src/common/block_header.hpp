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
	std::string serialize() const override;

	Serializable deserialize(const std::string& s) const override;
};

} // namespace ech