#pragma once

// Project includes
#include "crypto/byteset.hpp"

namespace ech
{

class TXID : public crypto::byteset<32u>
{
private:
public:
	explicit TXID(const std::string& id);
};

} // namespace ech