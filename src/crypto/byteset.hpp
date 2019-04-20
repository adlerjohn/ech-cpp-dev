#pragma once

// System includes
#include <algorithm>
#include <array>

// Library includes
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

namespace ech::crypto
{

/**
 * Like a bitset container, but for bytes. Fixed-size blob of bytes.
 */
template<uint64_t N>
class ByteSet
{
private:
	const std::array<std::byte, N> _data;

	static const auto hexToBytes(const std::string& str)
	{
		std::array<std::byte, N> data;

		if (str.length() % 2u != 0u)
			throw std::invalid_argument("hex string must have an even number of hexes");
		if (str.length() / 2u != N)
			throw std::invalid_argument("attempting to convert from hex string with invalid size");

		for (const auto& c : str) {
			static const std::string _hexes = std::string("0123456789abcdef");
			if (std::find(_hexes.begin(), _hexes.end(), c) == _hexes.end())
				throw std::invalid_argument("invalid hex char");
		}

		CryptoPP::StringSource(str, true,
			new CryptoPP::HexDecoder(
				new CryptoPP::ArraySink(reinterpret_cast<CryptoPP::byte*>(data.data()), N)
			)
		);

		return data;
	}

public:
	explicit ByteSet(const std::string& str)
		: _data(hexToBytes(str))
	{
	}

	const std::string toHex() const
	{
		std::string str;
		CryptoPP::ArraySource(reinterpret_cast<const CryptoPP::byte*>(this->_data.data()), N, true,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(str),
				false
			)
		);

		return str;
	}

	static const auto size() { return N; }

	const auto data() const { return this->_data; }

	friend bool operator==(const ByteSet<N>& lhs, const ByteSet<N>& rhs)
	{
		return lhs.data() == rhs.data();
	}

	friend bool operator<(const ByteSet<N>& lhs, const ByteSet<N>& rhs)
	{
		return std::memcmp(lhs.data().data(), rhs.data().data(), N) < 0;
	}

	friend bool operator>(const ByteSet<N>& lhs, const ByteSet<N>& rhs)
	{
		return std::memcmp(lhs.data().data(), rhs.data().data(), N) > 0;
	}

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