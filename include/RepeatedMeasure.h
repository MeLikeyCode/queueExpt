#pragma once

#include <chrono>
#include <functional>

/// Runs a function object repeatedly and measures the average execution time 
/// (as well as the standard deviation).
/// 
/// The "setup" function is run once before each run of the measured function.
/// The setup function can be used to reset the state of the measured function
/// prior to each execution.
///
/// Example Usage:
/// ~~~~~~~~~~~~~~~~
/// RepeatedMeasure m;
/// m.measure([](){
///     int a = 15 % 2 // testing how long it takes to do a modulo operation
/// });
/// m.mean(); // on average, how long did it take? (in nanoseconds)
/// ~~~~~~~~~~~~~~~~
///
/// Another example, one using the setup function:
/// ~~~~~~~~~~~~~~~~
/// std::vector<int> v;
///
/// RepeatedMeasure m;
/// m.setup([](){
///     v.clear();
/// });
///
/// m.measure([](){
///     v.push_back(1);
/// });
/// ~~~~~~~~~~~~~~~~
class RepeatedMeasure
{
public:
    void setup(const std::function<void()>& setupFunction);
    void measure(std::function<void()> func);

    long double meanNs() const;
    long double stdDevNs() const;
    long long numRuns() const;

private:
    long long _numRuns;
	long double _mean;
    long double _stdDev;
    std::function<void()> _setupFunction;
};