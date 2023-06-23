#include "CircularBufferQueue.h"

template<typename T, int S>
CircularBufferQueue<T,S>::CircularBufferQueue() :_buffer(), _front(0), _back(0), _size(0){
	if constexpr (S > 0) {
		_buffer.resize(S);
	}
	else {
		_buffer.resize(1); // start with a capacity of 1
	}
}

template<typename T, int S>
void CircularBufferQueue<T,S>::push_back(const T& value)
{
	if constexpr (S > 0) {
		assert(_size < capacity());
	}
	else {
		// resize if needed
		if (_size == capacity()) {
			reserve(_buffer.size() * 2);
		}
	}

	_buffer[_back] = value;

	//_back = (_back + 1) % capacity(); // ineffecient

	_back = (_back + 1);
	if (_back >= capacity())
		_back = _back % capacity();

	++_size;
}

template<typename T, int S>
void CircularBufferQueue<T,S>::pop_front()
{
	assert(_size > 0);

	//_front = (_front + 1) % capacity(); // ineffecient

	_front = (_front + 1);
	if (_front >= capacity())
		_front = _front % capacity();

	--_size;
}

template<typename T, int S>
T& CircularBufferQueue<T,S>::front()
{
	return const_cast<T&>(static_cast<const CircularBufferQueue<T,S>&>(*this).front());
}

template<typename T, int S>
const T& CircularBufferQueue<T,S>::front() const
{
	assert (_size > 0);

	return _buffer[_front];
}

template<typename T, int S>
const T& CircularBufferQueue<T,S>::back() const
{
	assert(_size > 0);

	return _buffer[_back - 1];
}

template<typename T, int S>
T& CircularBufferQueue<T,S>::back()
{
	return const_cast<T&>(static_cast<const CircularBufferQueue<T,S>&>(*this).back());
}

template<typename T, int S>
size_t CircularBufferQueue<T,S>::size() const
{
	return _size;
}

template<typename T, int S>
size_t CircularBufferQueue<T,S>::capacity() const
{
	return _buffer.size();
}

template<typename T, int S>
void CircularBufferQueue<T,S>::reserve(size_t newCapacity)
{
	size_t oldCapacity = capacity();
	if (newCapacity > oldCapacity)
	{
		std::vector<T> newBuffer(newCapacity);
		for (size_t i = 0; i < _size; ++i)
			newBuffer[i] = _buffer[(_front + i) % oldCapacity]; // TODO could be optimized by only doing % when needed

		_buffer = std::move(newBuffer);
		_front = 0;
		_back = _size;
	}
}
