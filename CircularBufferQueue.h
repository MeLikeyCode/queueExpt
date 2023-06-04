#pragma once

#include <vector>
#include <array>
#include <cassert>

/// A queue implemented using a circular buffer.
template <typename T>
class CircularBufferQueue
{
public:
	CircularBufferQueue(size_t maxSize);
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
	T& peek();
	const T& peek() const; // const version
	///@}

	/// Get the number of elements in the queue.
	size_t size() const;

	/// Get the maximum number of elements the queue can hold.
	size_t maxSize() const;

private:
	//std::array<T,100000> _buffer;
	std::vector<T> _buffer;
	size_t _front;		// front of the queue
	size_t _back;		// back of the queue (one past)
	size_t _size;		// number of elements currently in the 
	size_t _maxSize;
};

#include "CircularBufferQueue.tpp"