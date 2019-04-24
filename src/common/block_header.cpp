#include "block_header.hpp"

// Project includes
#include "deserializer.hpp"
#include "serializer.hpp"

using namespace ech;

const std::vector<std::byte> BlockHeader::serializeData(const uint32_t version, const crypto::Digest& prev, const crypto::Digest& depositsRoot, const crypto::Digest& transactionsRoot, const uint64_t height) const
{
	std::vector<std::byte> serial;

	const auto versionBytes = serializer::serialize<uint32_t, 4u>(version);
	serial.insert(serial.end(), versionBytes.begin(), versionBytes.end());

	serial.insert(serial.end(), prev.begin(), prev.end());

	const auto heightBytes = serializer::serialize<uint64_t, 8u>(height);
	serial.insert(serial.end(), heightBytes.begin(), heightBytes.end());

	serial.insert(serial.end(), depositsRoot.begin(), depositsRoot.end());

	serial.insert(serial.end(), transactionsRoot.begin(), transactionsRoot.end());

	return serial;
}

BlockHeader::BlockHeader(const uint32_t version, const crypto::Digest& prev, const crypto::Digest& depositsRoot, const crypto::Digest& transactionsRoot, const uint64_t height)
	: _id(crypto::Digest(serializeData(version, prev, depositsRoot, transactionsRoot, height)))
	, _version(version)
	, _prev(prev)
	, _depositsRoot(depositsRoot)
	, _transactionsRoot(transactionsRoot)
	, _height(height)
{
}

const BlockHeader BlockHeader::deserialize(std::vector<std::byte>& serial)
{
	const auto version = deserializer::deserialize<uint32_t, 4u>(serial);

	const auto prev = deserializer::move<crypto::Digest>(serial);

	const auto height = deserializer::deserialize<uint64_t, 8u>(serial);

	const auto depositsRoot = deserializer::move<crypto::Digest>(serial);

	const auto transactionsRoot = deserializer::move<crypto::Digest>(serial);

	return BlockHeader(version, prev, depositsRoot, transactionsRoot, height);
}

const std::vector<std::byte> BlockHeader::serialize() const
{
	std::vector<std::byte> serial;

	const auto serialData = serializeData(_version, _prev, _depositsRoot, _transactionsRoot, _height);
	serial.insert(serial.end(), serialData.begin(), serialData.end());

	return serial;
}