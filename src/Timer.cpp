#include "Timer.h"

Timer::Timer()
{
	_startTime = std::chrono::high_resolution_clock::now();
}

long long Timer::elapsedTimeNs() const
{
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(now - _startTime).count();
}

double Timer::elapsedTimeUs() const
{
	return elapsedTimeNs() / 1'000.0;
}

double Timer::elapsedTimeMs() const
{
	return elapsedTimeNs() / 1'000'000.0;
}

void Timer::restart()
{
	_startTime = std::chrono::high_resolution_clock::now();
}
