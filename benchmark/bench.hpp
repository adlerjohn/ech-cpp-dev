#pragma once

// System includes
#include <chrono>

namespace ech::benchmark
{

class Benchmark
{
private:
	std::chrono::high_resolution_clock::time_point _start;
	std::chrono::high_resolution_clock::time_point _finish;
public:
	virtual void setup() = 0;

	void before() {
		this->_start = std::chrono::high_resolution_clock::now();
	}

	virtual void run() = 0;

	void after() {
		this->_finish = std::chrono::high_resolution_clock::now();
	}

	auto getDuration() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(this->_finish - this->_start).count();
	}
};

} // namespace ech::benchmark