#pragma once

// System includes
#include <string>

namespace ech
{

class Serializable
{
	virtual std::string serialize() const;

	// TODO change to binary format
	virtual Serializable deserialize(const std::string& s) const;
};

} // namespace ech