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

	[[nodiscard]] static const auto serialize(const uint8_t in)
	{
		std::vector<std::byte> serial;

		static const size_t inSize = 1u;
		std::stringstream buf;
		buf << std::hex << std::setfill('0') << std::setw(inSize * 2) << in;
		const auto inBytes = crypto::byteset<inSize>(buf.str());
		serial.insert(serial.end(), inBytes.begin(), inBytes.end());

		return serial;
	}

	[[nodiscard]] static const auto serialize(const uint32_t in)
	{
		std::vector<std::byte> serial;

		static const size_t inSize = 4u;
		std::stringstream buf;
		buf << std::hex << std::setfill('0') << std::setw(inSize * 2) << in;
		const auto inBytes = crypto::byteset<inSize>(buf.str());
		serial.insert(serial.end(), inBytes.begin(), inBytes.end());

		return serial;
	}

	[[nodiscard]] static const auto serialize(const uint64_t in)
	{
		std::vector<std::byte> serial;

		static const size_t inSize = 8u;
		std::stringstream buf;
		buf << std::hex << std::setfill('0') << std::setw(inSize * 2) << in;
		const auto inBytes = crypto::byteset<inSize>(buf.str());
		serial.insert(serial.end(), inBytes.begin(), inBytes.end());

		return serial;
	}

	[[nodiscard]] static const auto serialize(const CoinAmount in)
	{
		std::vector<std::byte> serial;

		static const size_t inSize = 32u;
		std::stringstream buf;
		buf << std::hex << std::setfill('0') << std::setw(inSize * 2) << in;
		auto str = buf.str();
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		const auto inBytes = crypto::byteset<inSize>(str);
		serial.insert(serial.end(), inBytes.begin(), inBytes.end());

		return serial;
	}
};

} // namespace ech