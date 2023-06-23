#include <iostream>

#include "RepeatedMeasure.h"
#include <queue>
#include "CircularBufferQueue.h"

int main()
{
	std::queue<int> stdQueue{};
	CircularBufferQueue<int> circularBufferQueue{};

	RepeatedMeasure m;
	m.setup([&]() {
		// reset queues
		//stdQueue = std::queue<int>{};
		circularBufferQueue = CircularBufferQueue<int>{};
	});
	
	m.measure([&]() {
		circularBufferQueue.push_back(1);
	});

	std::cout << "NumRuns: " << m.numRuns() << std::endl;
	std::cout << "Mean: " << m.meanNs() / 1000 << std::endl;
	std::cout << "StdDev: " << m.stdDevNs() / 1000 << std::endl;

	return 0;
}
