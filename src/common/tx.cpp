#include "tx.hpp"

// Project includes
#include "serializer.hpp"

using namespace ech;

const std::vector<std::byte> TXData::serializeData(
	const uint32_t version,
	const std::vector<Input>& inputs,
	const std::vector<TXO>& outputs,
	const uint64_t heightMin,
	const uint64_t heightMax,
	const uint64_t recentBlockHeight,
	const crypto::Digest& recentBlockHash) const
{
	std::vector<std::byte> serial;

	const auto versionBytes = serializer::serialize<uint32_t, 4u>(version);
	serial.insert(serial.end(), versionBytes.begin(), versionBytes.end());

	const uint32_t inputsCount = inputs.size();
	const auto inputsCountBytes = serializer::serialize<uint32_t, 4u>(inputsCount);
	serial.insert(serial.end(), inputsCountBytes.begin(), inputsCountBytes.end());
	for (const auto& input : inputs) {
		const auto inputSerialized = input.serialize();
		serial.insert(serial.end(), inputSerialized.begin(), inputSerialized.end());
	}

	const uint32_t outputsCount = outputs.size();
	const auto outputsCountBytes = serializer::serialize<uint32_t, 4u>(outputsCount);
	serial.insert(serial.end(), outputsCountBytes.begin(), outputsCountBytes.end());
	for (const auto& output : outputs) {
		const auto outputSerialized = output.serialize();
		serial.insert(serial.end(), outputSerialized.begin(), outputSerialized.end());
	}

	const auto heightMinBytes = serializer::serialize<uint64_t, 8u>(heightMin);
	serial.insert(serial.end(), heightMinBytes.begin(), heightMinBytes.end());

	const auto heightMaxBytes = serializer::serialize<uint64_t, 8u>(heightMax);
	serial.insert(serial.end(), heightMaxBytes.begin(), heightMaxBytes.end());

	const auto recentBlockHeightBytes = serializer::serialize<uint64_t, 8u>(recentBlockHeight);
	serial.insert(serial.end(), recentBlockHeightBytes.begin(), recentBlockHeightBytes.end());
	if (recentBlockHeight > 0) {
		serial.insert(serial.end(), recentBlockHash.begin(), recentBlockHash.end());
	}

	return serial;
}

TXData::TXData(
	const uint32_t version,
	const std::vector<Input>& inputs,
	const std::vector<TXO>& outputs,
	const uint64_t heightMin,
	const uint64_t heightMax,
	const uint64_t recentBlockHeight,
	const crypto::Digest& recentBlockHash)
	: _id(serializeData(version, inputs, outputs, heightMin, heightMax, recentBlockHeight, recentBlockHash))
	, _version(version)
	, _inputs(inputs)
	, _outputs(outputs)
	, _heightMin(heightMin)
	, _heightMax(heightMax)
	, _recentBlockHeight(recentBlockHeight)
	, _recentBlockHash(recentBlockHash)
{
	// TODO do correctness checks (e.g., that each input refers to one existing witness)
}

const size_t TXData::getSize() const
{
	return serialize().size();
}

const std::vector<std::byte> TXData::serialize() const
{
	std::vector<std::byte> serial;

	serial.insert(serial.end(), _id.begin(), _id.end());

	const auto serialData = serializeData(_version, _inputs, _outputs, _heightMin, _heightMax, _recentBlockHeight, _recentBlockHash);
	serial.insert(serial.end(), serialData.begin(), serialData.end());

	return serial;
}

TX::TX(const TXData& data, const std::vector<crypto::Signature>& witnesses)
	: _data(data)
	, _witnesses(witnesses)
{
	// TODO do correctness checks (e.g., that each input refers to one existing witness)
}

const size_t TX::getSize() const
{
	return serialize().size();
}

const std::vector<std::byte> TX::serialize() const
{
	std::vector<std::byte> serial;

	const auto dataSerialized = _data.serialize();
	serial.insert(serial.end(), dataSerialized.begin(), dataSerialized.end());

	const uint32_t witnessesCount = _witnesses.size();
	const auto witnessesCountBytes = serializer::serialize<uint32_t, 4u>(witnessesCount);
	serial.insert(serial.end(), witnessesCountBytes.begin(), witnessesCountBytes.end());
	for (const auto& witness : _witnesses) {
		serial.insert(serial.end(), witness.begin(), witness.end());
	}

	return serial;
}
