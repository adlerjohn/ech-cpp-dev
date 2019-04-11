#include "byteset.hpp"

using namespace ech::crypto;

template<uint64_t N>
ByteSet<N>::ByteSet()
{
	this->_data.fill(std::byte(0));
}

template<uint64_t N>
ByteSet<N>::ByteSet(const std::string& hex)
{
	// TODO dew it
	this->_data.fill(std::byte(0));
}

template<uint64_t N>
std::string ByteSet<N>::toHex() const
{
	static const auto hexes = std::string("0123456789abcdef");

	auto offset = size_t(0);
	auto str = std::string(N*2, '0');

	for (auto& b : this->data)	{
		str.at(offset++) = hexes[(b >> 4) & 0x0f];
		str.at(offset++) = hexes[b & 0x0f];
	}

	return str;
}