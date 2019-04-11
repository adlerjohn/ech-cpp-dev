#pragma once

// System includes
#include <array>
#include <cstddef>

namespace ech::crypto
{

/**
 * Like a bitset container, but for bytes. Fixed-size blob of bytes.
 */
template<uint64_t N>
class ByteSet
{
private:
	std::array<std::byte, N> _data;
public:
	ByteSet()
	{
		this->_data.fill(std::byte(0));
	}

	explicit ByteSet(const std::string& hex)
	{
		// TODO dew it
		// TODO need to assert that the size of hex matches with N
		this->_data.fill(std::byte(0));
	}

	std::string toHex() const
	{
		static const auto hexes = std::string("0123456789abcdef");

		auto offset = size_t(0);
		auto str = std::string(N*2, '0');

		for (auto& b : this->_data)	{
			str.at(offset++) = hexes[(static_cast<uint8_t>(b) >> 4u) & 15u];
			str.at(offset++) = hexes[static_cast<uint8_t>(b) & 15u];
		}

		return str;
	}

	friend std::ostream& operator<<(std::ostream& os, const ByteSet<N>& o)
	{
		os << o.toHex();
		return os;
	}
};

// Make it look like bitset
template <uint64_t N>
using byteset = ByteSet<N>;

}