#pragma once

// Project includes
#include "crypto/byteset.hpp"

namespace ech
{

class UTXOID : public crypto::byteset<32u>
{
private:
public:
	explicit UTXOID(const std::string& id);
};

} // namespace ech