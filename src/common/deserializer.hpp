#pragma once

// System includes
#include <cstddef>

// Library includes
#include "crypto/byteset.hpp"

namespace ech
{
namespace deserializer
{

/**
 * Move bytes from the serialized representation directly into a byteset container.
 * @tparam T Type of byteset.
 * @param serial Serialized representation (will get modified).
 * @return Instance of T.
 */
template<class T>
[[nodiscard]] const T move(std::deque<std::byte>& serial)
{
	constexpr auto N = T::size();
	static_assert(std::is_base_of<crypto::ByteSet<N>, T>::value, "must move to byteset or child");

	if (serial.size() < N) {
		throw std::runtime_error("too few bytes when moving");
	}

	auto bytes = std::array<std::byte, N>();
	std::copy_n(serial.begin(), N, bytes.begin());

	serial.erase(serial.begin(), serial.begin() + N);

	return T(bytes);
}

// TODO change this to vector with index for beginning if benchmarking is slow
/**
 * Deserialize a primitive integer type.
 * @tparam T Type of integer.
 * @tparam B Size of integer, in bytes.
 * @param serial Serialized representation (will get modified).
 * @return Instance of T.
 */
template<class T, size_t B>
[[nodiscard]] const T deserialize(std::deque<std::byte>& serial)
{
	const auto bytes = move<crypto::byteset<B>>(serial);

	T t;

	for (const auto& byte : bytes) {
		t <<= 8;
		t |= static_cast<uint8_t>(byte);
	}

	return t;
}

} // namespace deserializer
} // namespace ech