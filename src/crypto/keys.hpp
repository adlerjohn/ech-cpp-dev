#pragma once

// System includes
#include <string>

// Project includes
#include "byteset.hpp"
#include "digest.hpp"

namespace ech::crypto
{

class PublicKey : public byteset<64>
{
public:
	PublicKey(const std::string& str);
};

class SecretKey : public byteset<32>
{
public:
	SecretKey(const std::string& str);

	auto sign(const Digest& msg);
	auto sign(const std::string& str);
};

} // namespace ech::crypto