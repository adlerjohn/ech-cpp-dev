#pragma once

// System includes
#include <algorithm>
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

	auto hexCharToByte(const char c) const
	{
		static const std::string _hexes = std::string("0123456789abcdef");
		if (std::find(_hexes.begin(), _hexes.end(), c) == _hexes.end())
			throw std::invalid_argument("invalid hex char in position 1");
		return (c >= 'A') ? (c - 'A') : (c - '0');
	}

public:
	ByteSet()
	{
		this->_data.fill(std::byte(0));
	}

	explicit ByteSet(const std::string& str)
	{
		auto raw_size = str.length();
		if (raw_size % 2u != 0u)
			throw std::invalid_argument("hex string must have an even number of hexes");
		const auto size = raw_size / 2u;
		if (size != N)
			throw std::invalid_argument("attempting to convert from hex string with invalid size");

		for (auto i = size_t(0); i < raw_size; i += 2u) {
			auto pos1 = str.at(i);
			auto pos2 = str.at(i + 1);

			this->_data.at(i / 2u) = static_cast<std::byte>(hexCharToByte(pos1) * 16u + hexCharToByte(pos2));
		}
	}

	std::string toHex() const
	{
		static const std::string _hexes = std::string("0123456789abcdef");

		auto offset = size_t(0);
		auto str = std::string(N * 2, '0');

		for (const auto& b : this->_data) {
			str.at(offset++) = _hexes.at((static_cast<uint8_t>(b) >> 4u) & 15u);
			str.at(offset++) = _hexes.at(static_cast<uint8_t>(b) & 15u);
		}

		return str;
	}

	auto getData() const { return this->_data; }

	friend std::ostream& operator<<(std::ostream& os, const ByteSet<N>& o)
	{
		os << o.toHex();
		return os;
	}
};

// Make it look like bitset
template<uint64_t N>
using byteset = ByteSet<N>;

} // namespace ech::crypto