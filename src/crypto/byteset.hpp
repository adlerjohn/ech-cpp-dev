#pragma once

// System includes
#include <algorithm>
#include <array>
#include <cstddef>

// Library includes
#include <crypto++/cryptlib.h>
#include <crypto++/filters.h>
#include <crypto++/hex.h>

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
	explicit ByteSet(const std::string& str)
	{
		if (str.length() % 2u != 0u)
			throw std::invalid_argument("hex string must have an even number of hexes");
		if (str.length() / 2u != N)
			throw std::invalid_argument("attempting to convert from hex string with invalid size");

		for (const auto& c : str) {
			static const std::string _hexes = std::string("0123456789abcdef");
			if (std::find(_hexes.begin(), _hexes.end(), c) == _hexes.end())
				throw std::invalid_argument("invalid hex char");
		}

		CryptoPP::HexDecoder decoder(new CryptoPP::ArraySink((byte*) this->_data.data(), N));
		CryptoPP::StringSource(str, true, new CryptoPP::Redirector(decoder));
	}

	std::string toHex() const
	{
		std::string str;
		auto dataStr = std::string((const char*) this->_data.data(), N);

		CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(str), false);
		CryptoPP::StringSource(dataStr, true, new CryptoPP::Redirector(encoder));

		return str;
	}

	static auto size() { return N; }

	auto data() const { return this->_data; }

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