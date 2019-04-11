#pragma once

// System includes
#include <string>

// Project includes
#include "byteset.hpp"
#include "digest.hpp"

namespace ech::crypto
{

class PublicKey : public byteset<64u>
{
public:
	PublicKey(const std::string& str);
};

class SecretKey : public byteset<32u>
{
public:
	SecretKey(const std::string& str);

	auto sign(const Digest& msg) const;
	auto sign(const std::string& str) const;
};

} // namespace ech::crypto