An experiment with writing a custom queue that is faster than std::queue (for my use case). The custom queue is a circular buffer queue.

![](docs/time_ratio.png)

There are two versions of the custom queue. One is fixed size, the other can dynamically grow. The dynamically growable one is about **30%** faster than std::queue. The fixed size one is about **50%** faster than std::queue.

The fixed version is about **16%** faster than the non-fixed version.

# Files
- `benchmark.cpp` - Contains benchmarking code. Uses catch2's benchmarking functionality to measure how long push()/peek()/pop() operations take in std::queue and in the custom queue(s).
- `test.cpp` - Contains tests that verify basic functionality of the custom queue(s). Also produces an executable (i.e. has a main()) that *runs* both the tests and the benchmarks.
- `CircularBufferQueue.h/.tpp` - the custom queue class. Is templated on the type of the elements in the queue, as well as the size of the queue (optional). If you specify a size, you get a fixed size queue, otherwise you get a dynamically growable one. 
- `plot.py` - when ran, produces plots comparing the runtimes of std::queue vs the custom queue(s)
    - right now, you have to manually take the numbers that test.cpp outputs, put them in plot.py, and then run plot.py :/
 
# What is the down side?
The down side of this custom queue is since it stores the objects contegeously in memory, when you need to store really big objects, you will need a large *contigeous* allocation, which is much harder to find than many smaller allocations. However, this was fine for my use case. I had many small objects and I needed to constantly read/write to the queue (in a tight loop).

# Why is the fixed sized better than the dynamic sized one?
The fixed size circular buffer has a fixed size, so it doesn’t have to check if it needs to grow. The non-fixed size circular buffer has to check if it needs to grow, this checking is not free, it’s an if statement, and if it does need to grow it’s even worse, because it now has to allocate a new array and copy all the items over. So both the checking and the allocating/copying are overhead that the fixed size circular buffer doesn’t have!

A note on if statements. They are expensive. Especially if the CPU's branch predictor predicts the wrong branch, the CPU cache goes cold and things slow down like crazy.
