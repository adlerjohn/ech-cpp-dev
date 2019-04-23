#pragma once

// Project includes
#include "serializable.hpp"

namespace ech
{

/**
 * Deposit "transaction" from parent chain.
 */
class Deposit : public Serializable
{
private:
public:
	[[nodiscard]] const std::vector<std::byte> serialize() const override;
};

} // namespace ech