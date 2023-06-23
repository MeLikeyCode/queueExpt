#include "RepeatedMeasure.h"

void RepeatedMeasure::setup(const std::function<void()>& setupFunction) {
    _setupFunction = setupFunction;
}

void RepeatedMeasure::measure(std::function<void()> func) {
    _numRuns = 0;
    long double runtimeSum = 0;
    long double runtimeSquaredSum = 0;

    // do 10 runs to get a rough estimate of the runtime
    for (size_t i = 0; i < 10; i++) {
        if (_setupFunction)
            _setupFunction();
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto runtime = end - start;
        _numRuns++;
        runtimeSum += runtime.count();
        runtimeSquaredSum += std::pow(runtime.count(), 2); // TODO might be faster to do x * x instead of x**2
        _mean = runtimeSum / _numRuns;
        long double variance = runtimeSquaredSum / _numRuns - std::pow(_mean, 2);
        _stdDev = std::sqrt(variance);
    }

    // do more runs until the standard deviation is less than 1% of the mean
    do {
        if (_setupFunction)
            _setupFunction();
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto runtime = end - start;
        _numRuns++;
        runtimeSum += runtime.count();
        runtimeSquaredSum += std::pow(runtime.count(), 2); // TODO might be faster to do x * x instead of x**2
        _mean = runtimeSum / _numRuns;
        long double variance = runtimeSquaredSum / _numRuns - std::pow(_mean, 2);
        _stdDev = std::sqrt(variance);
    } while ((_stdDev > 0.01 * _mean) && (_numRuns < LLONG_MAX));
}

long double RepeatedMeasure::meanNs() const {
    return _mean;
}

long double RepeatedMeasure::stdDevNs() const {
    return _stdDev;
}

long long RepeatedMeasure::numRuns() const {
    return _numRuns;
}
