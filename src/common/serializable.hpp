#pragma once

// System includes
#include <cstddef>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// Project includes
#include "coin_amount.hpp"
#include "crypto/byteset.hpp"

namespace ech
{

class Serializable
{
public:
	[[nodiscard]] virtual const std::vector<std::byte> serialize() const = 0;

	[[nodiscard]] const std::string toHex() const
	{
		std::stringstream buf;
		buf << std::hex << std::setfill('0');
		for (const auto& c : serialize())
			buf << std::setw(2) << static_cast<int>(c);

		return buf.str();
	}
};

} // namespace ech