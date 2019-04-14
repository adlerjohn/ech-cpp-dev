#include "signature.hpp"

// System includes
// TODO remove
#include <iostream>
#include <iomanip>

// Library includes
#include <crypto++/eccrypto.h>
#include <crypto++/modarith.h>
#include <crypto++/nbtheory.h>
#include <crypto++/oids.h>
#include <crypto++/osrng.h>

using namespace ech::crypto;

Signature::Signature(const std::string& sig)
	: ByteSet(sig)
{
}

Signature::Signature(const std::string& str, const SecretKey& secretKey)
	: Signature(secretKey.sign(str))
{
}

PublicKey Signature::recover(const Digest& digest) const
{
	std::cout << this->toHex() << std::endl;

	const auto sig = this->toHex();
	const auto r = sig.substr(0, 64);
	const auto s = sig.substr(64, 64);
	const auto v = sig.substr(128, 2);

	const auto ri = CryptoPP::Integer(std::string("0x" + r).c_str());
	const auto si = CryptoPP::Integer(std::string("0x" + s).c_str());
	const auto vi = CryptoPP::Integer(std::string("0x" + v).c_str());

	// r is the x coordinate of the ephemeral key
	const auto ex = ri;

	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pk;
	pk.AccessGroupParameters().Initialize(CryptoPP::ASN1::secp256k1());

	const auto curve = pk.GetGroupParameters().GetCurve();
	// Field size
	const auto P = curve.FieldSize();
	// A
	const auto A = curve.GetA();
	// B
	const auto B = curve.GetB();
	// Curve generator point coordinates
	const auto G = pk.GetGroupParameters().GetSubgroupGenerator();
	// Group order
	const auto N = pk.GetGroupParameters().GetGroupOrder();

	const auto ey_tmp = ((ex*ex + A) * ex + B) % P;
	auto ey = CryptoPP::ModularSquareRoot(ey_tmp, P);
	if (!(vi % 2 ^ ey % 2))
		ey = P - ey;
	// If ey_tmp is not a quadratic residue, then r cannot be the x coord for
	// a point on the curve, and so the sig is invalid
	if ((ey_tmp - ey * ey) % P != 0 || !(ri % N) || !(si % N))
		throw std::runtime_error("invalid signature");

	const auto epoint = CryptoPP::ECPPoint(CryptoPP::Integer(ex), CryptoPP::Integer(ey));

	const auto di = CryptoPP::Integer(std::string("0x" + digest.toHex()).c_str());

	const auto Gz = curve.ScalarMultiply(G, (N - di) % N);
	const auto XY = curve.ScalarMultiply(epoint, si);
	const auto Qr = curve.Add(Gz, XY);
	const auto Q = curve.ScalarMultiply(Qr, curve.GetField().MultiplicativeInverse(ri));

	pk.SetPublicElement(Q);

	// Validate ephemeral public key
	CryptoPP::AutoSeededRandomPool prng;
	bool result = pk.Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid public key");

	// Now calculate public key from ephemeral public key

	const auto point = pk.GetPublicElement();
	std::stringstream buf;
	buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(point.x, 16u);
	buf << std::setw(64) << std::setfill('0') << CryptoPP::IntToString(point.y, 16u);
	const auto publicKey = buf.str();

	std::cout << publicKey.size() << " " << publicKey << std::endl;

	return PublicKey(publicKey);
}

PublicKey Signature::recover(const std::string& msg) const
{
	return recover(Digest(msg));
}

bool Signature::verify(const Digest& digest, const PublicKey& publicKey) const
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pk;
	pk.AccessGroupParameters().Initialize(CryptoPP::ASN1::secp256k1());

	auto hexPublicKey = publicKey.toHex();
	auto px = std::string("0x" + hexPublicKey.substr(0, PublicKey::size()));
	auto py = std::string("0x" + hexPublicKey.substr(PublicKey::size(), PublicKey::size()));
	auto point = CryptoPP::ECPPoint(CryptoPP::Integer(px.c_str()), CryptoPP::Integer(py.c_str()));
	pk.SetPublicElement(point);

	// Validate public key
	CryptoPP::AutoSeededRandomPool prng;
	bool result = pk.Validate(prng, 3);
	if (!result)
		throw std::runtime_error("invalid public key");

	// Slice off v from signature
	auto hexSig = this->toHex().substr(0, (Signature::size() - 1) * 2);
	std::cout << hexSig.length() << " " << hexSig << std::endl;

	std::string decodedSignature;
	CryptoPP::StringSource(hexSig, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decodedSignature)
		)
	);

	std::string decodedDigest;
	CryptoPP::StringSource(digest.toHex(), true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decodedDigest)
		)
	);

	// Verify
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Verifier verifier(pk);
	CryptoPP::StringSource(decodedSignature + decodedDigest, true,
		new CryptoPP::SignatureVerificationFilter(verifier,
			new CryptoPP::ArraySink((byte*) &result, sizeof(result))
		)
	);

	return result;
}

bool Signature::verify(const std::string& msg, const PublicKey& publicKey) const
{
	return verify(Digest(msg), publicKey);
}

bool Signature::verify(const Digest& digest) const
{
	return verify(digest, this->recover(digest));
}

bool Signature::verify(const std::string& msg) const
{
	return verify(Digest(msg));
}