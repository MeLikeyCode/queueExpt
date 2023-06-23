import matplotlib.pyplot as plt
import numpy as np

input_sizes = [100, 1000, 10000, 100000, 1000000, 10000000, 100000000] # number of elements in the queue

# time in microseconds taken by circular buffer queue and std::queue, to add said number of elements
# to the queue, and then remove them
# this is taken from the output of the C++ benchmarkings (see tests.cpp)
circular_times = np.array([0.254439, 2.34656, 24.254, 243.604, 2486.9, 25105.9, 250000])
circular_times_fixed = np.array([0.21601, 2.07382, 20.598, 230.7, 2042.26, 20511.3, 213000])
std_times = np.array([0.294727, 2.74086, 27.803, 276.306, 3057.88, 38526.9, 393000])

def plot(x, y1, y2, title, filename):
    time_ratio = y2 / y1

    plt.figure(figsize=(10, 6))
    plt.plot(x, time_ratio)
    plt.title(title)
    plt.xlabel('input size')
    plt.ylabel('time ratio')
    plt.ylim(0, max(time_ratio) + 1)
    
    plt.xscale('log')

    plt.savefig(filename)

plot(input_sizes, circular_times, std_times, "time ratio: std::queue / CircularBufferQueue (non-fixed size)","time_ratio.png")
plot(input_sizes, circular_times_fixed, std_times, "time ratio: std::queue / CircularBufferQueue (fixed size)", "time_ratio_fixed.png")
plot(input_sizes, circular_times_fixed, circular_times, "time ratio: CircularBufferQueue (non-fixed size) / CircularBufferQueue (fixed size)","time_ratio_nonfixed_fixed.png")

print(f'average ratio: {np.average(std_times / circular_times)}')
print(f'average ratio fixed: {np.average(std_times / circular_times_fixed)}')
print(f'average ratio nonfixed to fixed: {np.average(circular_times / circular_times_fixed)}')
