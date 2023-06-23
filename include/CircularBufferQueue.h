#pragma once

#include <vector>
#include <cassert>

/// A queue implemented using a circular buffer.
///@tparam T The type of the elements in the queue.
///@tparam S The max size of the queue. If -1 (default), the queue can grow to any size (but push/pop/peek operations are a bit slower).
template <typename T, int S = -1>
class CircularBufferQueue
{
public:
	CircularBufferQueue();
	~CircularBufferQueue() = default;

	// prevent copying
	CircularBufferQueue(const CircularBufferQueue&) = delete;
	CircularBufferQueue& operator=(const CircularBufferQueue&) = delete;
	
	// allow moving
	CircularBufferQueue(CircularBufferQueue&&) = default;
	CircularBufferQueue& operator=(CircularBufferQueue&&) = default;

	/// Add an element to the back.
	void push_back(const T& value);

	/// Remove the element at the front.
	void pop_front();

	/// Get the element at the front.
	///@{
	T& front();
	const T& front() const; // const version
	///@}

	/// Get the element at the back.
	///@{
	T& back();
	const T& back() const; // const version
	///@}

	/// Get the number of elements in the queue.
	size_t size() const;

	/// Get the maximum number of elements the queue can hold.
	/// If the queue is not fixed size, it will resize once this
	/// capacity is reached. If the queue is fixed size, it
	/// will never resize and it is upto the client to ensure
	/// the initial capacity specified as the template S argument
	/// is never exceeded.
	size_t capacity() const;

	/// Resize the queue to the given capacity.
	/// If the capacity is less than the current capacity, does nothing.
	void reserve(size_t newCapacity);

private:
	std::vector<T> _buffer;
	size_t _front;		// front of the queue
	size_t _back;		// back of the queue (one past)
	size_t _size;		// number of elements currently in the 
	size_t _maxSize = S;// max size of the queue, only applies to fixed size queues
};

// typedef for fixed size queue
template <typename T>
using CircularBufferQueueFixed = CircularBufferQueue<T, -1>;

#include "CircularBufferQueue.tpp"