import matplotlib.pyplot as plt
import numpy as np

input_sizes = [100, 1000, 10000, 100000, 1000000, 10000000] # number of elements in the queue

# time in microseconds taken by circular buffer queue and std::queue, to add said number of elements
# to the queue, and then remove them
# this is taken from the output of the C++ benchmarkings (see tests.cpp)
circular_times_inefficient = np.array([0.501595, 5.042, 50.249, 509.79, 5020.54, 50351.3])
circular_times_efficient = np.array([0.206245, 1.95117, 20.3255, 211.976,2043.87,20615.5])
std_times = np.array([0.372727, 2.94086, 29.803, 285.306, 3157.88, 39526.9])

def plot(trial):
    # trial is either "efficient" or "inefficient

    if trial == "efficient":
        circular_times = circular_times_efficient
    else:
        circular_times = circular_times_inefficient
        
    # create figure for raw timings 
    plt.figure(figsize=(10, 6))
    plt.plot(input_sizes, circular_times, label='CircularBufferQueue')
    plt.plot(input_sizes, std_times, label='std::queue')
    plt.title('custom circular buffer vs std::queue (raw data)')
    plt.xlabel('input size')
    plt.ylabel('time taken (us)')
    plt.legend()

    plt.xscale('log')

    plt.savefig(f'raw_timings_{trial}.png')

    # create figure for time ratio
    time_ratio = std_times / circular_times

    plt.figure(figsize=(10, 6))
    plt.plot(input_sizes, time_ratio)
    plt.title('time taken by std::queue / time taken by custom circular buffer')
    plt.xlabel('input size')
    plt.ylabel('std::queue / circular buffer')
    plt.ylim(0, max(time_ratio) + 1)

    plt.xscale('log')

    plt.savefig(f'time_ratio_{trial}.png')

plot("efficient")
plot("inefficient")