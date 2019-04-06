#pragma once

// System includes
#include <string>

class Serializable
{
	virtual std::string serialize() const;
	// TODO change to binary format
	virtual Serializable deserialize(std::string s) const;
};