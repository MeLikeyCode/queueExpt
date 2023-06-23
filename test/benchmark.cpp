#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

#include <queue>

#include "CircularBufferQueue.h"

TEST_CASE("batch pushing then batch peek/pop") {
	for (size_t numItems = 100; numItems <= 100000000; numItems *= 10) {
		CircularBufferQueue<int,100000000> circularBuffer{};
		std::queue<int> stdQueue;

		BENCHMARK("circular buffer queue: " + std::to_string(numItems) + " items") {
			for (size_t i = 0; i < numItems; i++)
				circularBuffer.push_back(i);
			for (size_t i = 0; i < numItems; i++) {
				auto& front = circularBuffer.front();
				circularBuffer.pop_front();
			}
		};

		BENCHMARK("std::queue: " + std::to_string(numItems) + " items") {
			for (size_t i = 0; i < numItems; i++)
				stdQueue.push(i);
			for (size_t i = 0; i < numItems; i++) {
				auto& front = stdQueue.front();
				stdQueue.pop();
			}
		};
	}
}
