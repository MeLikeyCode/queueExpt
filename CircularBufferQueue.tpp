#pragma once

template<typename T>
CircularBufferQueue<T>::CircularBufferQueue(size_t maxSize) :_maxSize(maxSize), _buffer(), _front(0), _back(0), _size(0){
	_buffer.resize(maxSize);
}

template<typename T>
void CircularBufferQueue<T>::push_back(const T& value)
{
	assert(_size < maxSize());

	_buffer[_back] = value;

	//_back = (_back + 1) % maxSize();

	_back = (_back + 1);
	if (_back >= maxSize())
		_back = _back % maxSize();

	++_size;
}

template<typename T>
void CircularBufferQueue<T>::pop_front()
{
	assert(_size > 0);

	//T value = _buffer[_front];

	//_front = (_front + 1) % maxSize();

	_front = (_front + 1);
	if (_front >= maxSize())
		_front = _front % maxSize();

	--_size;

	//return value;
}

template<typename T>
T& CircularBufferQueue<T>::peek()
{
	return _buffer[_front];
}

template<typename T>
const T& CircularBufferQueue<T>::peek() const
{
	return _buffer[_front];
}

template<typename T>
size_t CircularBufferQueue<T>::size() const
{
	return _size;
}

template<typename T>
size_t CircularBufferQueue<T>::maxSize() const
{
	//return _buffer.size();
	return _maxSize;
}

