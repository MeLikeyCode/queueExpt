#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

#include <queue>

#include "CircularBufferQueue.h"

TEST_CASE("CircularBufferQueue") {
	CircularBufferQueue<int> queue{10};
	REQUIRE(queue.size() == 0);
	REQUIRE(queue.maxSize() == 10);

	SECTION("adding items behaves properly") {
		queue.push_back(1);
		CHECK(queue.size() == 1);
		CHECK(queue.peek() == 1);

		queue.push_back(2);
		CHECK(queue.size() == 2);
		CHECK(queue.peek() == 1);

		queue.push_back(3);
		CHECK(queue.size() == 3);
		CHECK(queue.peek() == 1);
	}

	SECTION("removing items behaves properly") {
		queue.push_back(1);
		queue.push_back(2);
		queue.push_back(3);

		CHECK(queue.peek() == 1);
		queue.pop_front();
		CHECK(queue.peek() == 2);
		CHECK(queue.size() == 2);

		queue.pop_front();
		CHECK(queue.peek() == 3);
		CHECK(queue.size() == 1);

		queue.pop_front();
		CHECK(queue.size() == 0);
	}

	SECTION("wraps around properly") {

		// fill it up and empty it a couple times
		for (size_t j = 0; j < 3; j++) {

			// fill it up
			for (size_t i = 0; i < 10; i++)
				queue.push_back(i);

			// remove all items
			for (size_t i = 0; i < 10; i++)
			{
				CHECK(queue.peek() == i);
				queue.pop_front();
			}
		}
	}
}