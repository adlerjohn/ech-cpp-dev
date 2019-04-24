#pragma once

// System includes
#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <vector>

// Library includes
#include "crypto/byteset.hpp"

namespace ech
{
namespace serializer
{

template<class T, size_t B>
[[nodiscard]] const auto serialize(const T in)
{
	std::vector<std::byte> serial;

	std::stringstream buf;
	buf << std::hex << std::setfill('0') << std::setw(B * 2) << in;
	auto str = buf.str();
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	const auto inBytes = crypto::byteset<B>(str);
	serial.insert(serial.end(), inBytes.begin(), inBytes.end());

	return serial;
};

} // namespace serializer
} // namespace ech