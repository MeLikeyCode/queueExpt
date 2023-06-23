#pragma once

#include <chrono>

/// A timer object that can be used to effeciently and accurately measure how much time elpases between certain points.
/// 
/// Example usage:
/// ~~~~~~~~~~~~~~~~~~~~~~
/// Timer timer; // starts the timer
/// // do something
/// long long elapsedTime = timer.elapsedTimeNs(); // time elapsed since the timer was started
///
/// timer.restart(); // restarts the timer
/// // do something else
/// long long elapsedTime2 = timer.elapsedTimeNs(); // time elapsed since the restart
/// ~~~~~~~~~~~~~~~~~~~~~~
class Timer
{
public:
	/// Constructs a timer and starts it.
	Timer();

	/// Time elapsed since the timer was started (or restarted).
	/// You can get the elapsed time in nanoseconds (Ns), microseconds (Us) or milliseconds (Ms).
	///@{
	long long elapsedTimeNs() const;
	double elapsedTimeUs() const;
	double elapsedTimeMs() const;
	///@}

	/// Restart the timer.
	void restart();

private:
	std::chrono::high_resolution_clock::time_point _startTime;
};