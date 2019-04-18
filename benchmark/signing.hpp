#pragma once

// Project includes
#include "bench.hpp"

namespace ech::benchmark
{

class Signing : public Benchmark
{
private:
public:
	void run() override;
};

} // namespace ech::benchmark