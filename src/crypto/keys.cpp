#include "keys.hpp"

using namespace ech::crypto;

PublicKey::PublicKey(const std::string& str)
	: ByteSet(str)
{
}

SecretKey::SecretKey(const std::string& str)
	: ByteSet(str)
{
}

auto SecretKey::sign(const Digest& msg)
{
	// TODO implement
	return nullptr;
}

auto SecretKey::sign(const std::string& str)
{
	// TODO implement
	return nullptr;
}
