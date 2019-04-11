#pragma once

// Project includes
#include "byteset.hpp"

namespace ech::crypto
{

using PublicKey = byteset<64>;
using SecretKey = byteset<32>;

} // namespace ech::crypto