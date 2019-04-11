#pragma once

// Project includes
#include "byteset.hpp"

namespace ech::crypto
{

using PublicKey = ByteSet<64>;
using SecretKey = ByteSet<32>;

} // namespace ech::crypto