#include "byteset.hpp"

#include <string>

using namespace ech::crypto;

template<uint64_t N>
const std::string ByteSet<N>::_hexes = std::string("0123456789abcdef");