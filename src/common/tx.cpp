#include "tx.hpp"

using namespace ech;

const std::vector<std::byte> TX::serializeData(
	const std::vector<Input>& inputs,
	const std::vector<TXO>& outputs,
	const std::vector<crypto::Signature>& witnesses,
	const uint64_t heightMin,
	const uint64_t heightMax,
	const uint64_t recentBlockHeight,
	const crypto::Digest& recentBlockHash) const
{
	std::vector<std::byte> serial;

	const uint32_t inputsCount = inputs.size();
	const auto inputsCountBytes = Serializable::serialize(inputsCount);
	serial.insert(serial.end(), inputsCountBytes.begin(), inputsCountBytes.end());
	for (const auto& input : inputs) {
		const auto inputSerialized = input.serialize();
		serial.insert(serial.end(), inputSerialized.begin(), inputSerialized.end());
	}

	const uint32_t outputsCount = outputs.size();
	const auto outputsCountBytes = Serializable::serialize(outputsCount);
	serial.insert(serial.end(), outputsCountBytes.begin(), outputsCountBytes.end());
	for (const auto& output : outputs) {
		const auto outputSerialized = output.serialize();
		serial.insert(serial.end(), outputSerialized.begin(), outputSerialized.end());
	}

	const uint32_t witnessesCount = witnesses.size();
	const auto witnessesCountBytes = Serializable::serialize(witnessesCount);
	serial.insert(serial.end(), witnessesCountBytes.begin(), witnessesCountBytes.end());
	for (const auto& witness : witnesses) {
		serial.insert(serial.end(), witness.begin(), witness.end());
	}

	const auto heightMinBytes = Serializable::serialize(heightMin);
	serial.insert(serial.end(), heightMinBytes.begin(), heightMinBytes.end());

	const auto heightMaxBytes = Serializable::serialize(heightMax);
	serial.insert(serial.end(), heightMaxBytes.begin(), heightMaxBytes.end());

	const auto recentBlockHeightBytes = Serializable::serialize(recentBlockHeight);
	serial.insert(serial.end(), recentBlockHeightBytes.begin(), recentBlockHeightBytes.end());
	if (recentBlockHeight > 0) {
		serial.insert(serial.end(), recentBlockHash.begin(), recentBlockHash.end());
	}

	return serial;
}

TX::TX(
	const std::vector<Input>& inputs,
	const std::vector<TXO>& outputs,
	const std::vector<crypto::Signature>& witnesses,
	const uint64_t heightMin,
	const uint64_t heightMax,
	const uint64_t recentBlockHeight,
	const crypto::Digest& recentBlockHash)
	: _id(serializeData(inputs, outputs, witnesses, heightMin, heightMax, recentBlockHeight, recentBlockHash))
	, _inputs(inputs)
	, _outputs(outputs)
	, _witnesses(witnesses)
	, _heightMin(heightMin)
	, _heightMax(heightMax)
	, _recentBlockHeight(recentBlockHeight)
	, _recentBlockHash(recentBlockHash)
{
	// TODO do correctness checks (e.g., that each input refers to one existing witness)
}

const size_t TX::getSize() const
{
	return serialize().size();
}

const bool TX::verify(const State& state) const
{
	// TODO implement
	// To verify a transaction is valid, we need to
	// 1) for each input
	//  a) recover the address from the signature, using tx data hash
	//  b) check that the UTXO being spent exists in the state and owner matches
	// 2) sum inputs <= sum outputs (including colored coins)
	return false;
}
const std::vector<std::byte> TX::serialize() const
{
	std::vector<std::byte> serial;

	serial.insert(serial.end(), _id.begin(), _id.end());

	const auto serialData = serializeData(_inputs, _outputs, _witnesses, _heightMin, _heightMax, _recentBlockHeight, _recentBlockHash);
	serial.insert(serial.end(), serialData.begin(), serialData.end());

	return serial;
}