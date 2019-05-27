#include "sparse_merkle.hpp"

// System includes
#include <cassert>

using namespace ech;

SMTNode::SMTNode(const crypto::Digest& key, const crypto::Digest& digest)
	: _key(key)
	, _digest(digest)
{
}

const auto SMTNode::descend(const bool isLeft)
{
	if (isLeft) {
		return this->getLeft().get();
	}

	return this->getRight().get();
}

const crypto::Digest SparseMerkleTree::defaultNodeValue()
{
	return crypto::Digest("0000000000000000000000000000000000000000000000000000000000000000", true);
}

const auto SparseMerkleTree::keyToPath(const crypto::Digest& key)
{
	std::vector<bool> path;

	static const auto zero = std::byte(0);
	static const auto one = std::byte(1);

	path.reserve(crypto::Digest::size() * 8u);
	for (const auto& byte : key) {
		// 8 bits in a byte
		for (auto i = 0u; i < 8u; i++) {
			path.push_back((byte & one << i) == zero);
		}
	}

	return path;
}

const auto SparseMerkleTree::hashSubtree(const crypto::Digest& key, const std::vector<bool>& path, const size_t offset)
{
	auto digest = key;

	// TODO check off-by-one
	for (size_t i = path.size() - 1; i > offset; i--) {
		if (path.at(i)) {
			digest = digest + defaultNodeValue();
		} else {
			digest = defaultNodeValue() + digest;
		}
	}

	return digest;
}

SparseMerkleTree::SparseMerkleTree()
	: _root(nullptr)
{
}

const bool SparseMerkleTree::at(const crypto::Digest& key) const
{
	if (_root == nullptr) {
		return false;
	}

	const auto path = keyToPath(key);
	auto val = false;

	auto node = _root.get();
	if (node->isLeaf()) {
		if (node->getKey() == key) {
			val = true;
		}
		return val;
	}

	for (const auto& isLeft : path) {
		node = node->descend(isLeft);

		if (node->isLeaf()) {
			if (node->getKey() == key) {
				val = true;
			}
			break;
		}
	}

	return val;
}

const void SparseMerkleTree::insert(const crypto::Digest& key)
{
	const auto path = keyToPath(key);

	if (_root == nullptr) {
		const auto digest = hashSubtree(key, path, 0);
		auto newNode = std::make_unique<SMTNode>(key, digest);
		_root = std::move(newNode);

		return;
	}

	auto node = _root.get();
	for (size_t i = 0; i < path.size(); i++) {
		auto prev = node;
		node = node->descend(path.at(i));

		if (node->isLeaf()) {
			if (node->getKey() != key) {
				assert(i != path.size() - 1);

				const auto otherPath = keyToPath(node->getKey());
				assert(path.size() == otherPath.size());

				for (; i < path.size(); i++) {
					assert(i != path.size() - 1);

					auto newParent = std::make_unique<SMTNode>(defaultNodeValue(), defaultNodeValue());
					newParent->setParent(prev);
					auto otherNode = [prev, path, i]() -> auto {
						if (path.at(i)) {
							return prev->moveLeft();
						} else {
							return prev->moveRight();
						}
					}();
					otherNode->setParent(newParent.get());

					if (path.at(i + 1) != otherPath.at(i + 1)) {
						// If the next step differs
						const auto digest = hashSubtree(key, path, i + 1);
						auto newNode = std::make_unique<SMTNode>(key, digest);
						newNode->setParent(newParent.get());

						auto parentNode = newNode->getParent();
						// TODO check for off-by-one
						for (size_t j = i; j >= 0; j--) {
							if (path.at(j)) {
								const auto otherDigest = parentNode->hasRight() ? parentNode->getRight()->getDigest() : defaultNodeValue();
								parentNode->setDigest(parentNode->getLeft()->getDigest() + otherDigest);
							} else {
								const auto otherDigest = parentNode->hasLeft() ? parentNode->getLeft()->getDigest() : defaultNodeValue();
								parentNode->setDigest(otherDigest + parentNode->getRight()->getDigest());
							}
							parentNode = parentNode->getParent();
						}

						if (path.at(i + 1)) {
							newParent->setLeft(std::move(newNode));
							newParent->setRight(std::move(otherNode));
						} else {
							newParent->setLeft(std::move(otherNode));
							newParent->setRight(std::move(newNode));
						}
					} else {
						// If the next step is the same
						if (path.at(i + 1)) {
							newParent->setLeft(std::move(otherNode));
							newParent->setRight(nullptr);
						} else {
							newParent->setLeft(nullptr);
							newParent->setRight(std::move(otherNode));
						}
					}

					if (path.at(i)) {
						// If we just descended left
						prev->setLeft(std::move(newParent));
					} else {
						// If we just descended right
						prev->setRight(std::move(newParent));
					}

					if (path.at(i + 1) != otherPath.at(i + 1)) {
						break;
					}

					node = node->descend(path.at(i + 1));
				}
			}

			// TODO else: update value since we're at the bottom of the tree

			return;
		}
	}
}

const void SparseMerkleTree::erase(const crypto::Digest& key)
{
}

const auto SparseMerkleTree::getInclusionProof(const crypto::Digest& key) const
{
	std::vector<std::optional<crypto::Digest>> path;

	return path;
}

const auto SparseMerkleTree::getExclusionProof(const crypto::Digest& key) const
{
	std::vector<std::optional<crypto::Digest>> path;

	return path;
}

const bool SparseMerkleTree::checkInclusionProof(const std::vector<bool>& path, const std::vector<std::optional<crypto::Digest>>& hashes) const
{
	return false;
}

const bool SparseMerkleTree::checkExclusionProof(const std::vector<bool>& path, const std::vector<std::optional<crypto::Digest>>& hashes) const
{
	return false;
}
