#pragma once

// System includes
#include <cstddef>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace ech
{

class Serializable
{
protected:
	const std::vector<std::byte> _serialized;
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