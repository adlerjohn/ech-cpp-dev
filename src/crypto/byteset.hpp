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
	ByteSet() { this->_data.fill(std::byte(0)); }
};

}