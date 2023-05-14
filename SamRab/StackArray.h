#pragma once
#include "Stack.h"
#include "StackExceptions.h"

template<class T>
class StackArray : public Stack<T>
{
private:
	T* array_ = nullptr;
	size_t top_ = 0;
	size_t size_ = 0;

public:
	StackArray(size_t size = 128);
	~StackArray();

	StackArray(const StackArray<T>& src) = delete;
	StackArray(StackArray<T>&& src) = delete;
	StackArray& operator=(const StackArray<T>& src) = delete;
	StackArray& operator=(const StackArray<T>&& src) = delete;

	void push(const T& e) override;
	T pop() override;
	bool isEmpty() override;
	T peek();
};

template<class T>
inline StackArray<T>::StackArray(size_t size)
{
	this->size_ = size;
	this->top_ = 0;
	this->array_ = new T[size]{};
}

template<class T>
inline StackArray<T>::~StackArray()
{
	delete array_;
}

template<class T>
inline void StackArray<T>::push(const T& e)
{
	if (top_ >= size_)
	{
		throw StackOverflowException();
	}
	this->array_[top_++] = e;
}

template<class T>
inline T StackArray<T>::pop()
{
	if (top_ <= 0)
	{
		throw StackUnderflowException();
	}
	return array_[--top_];
}

template<class T>
inline bool StackArray<T>::isEmpty()
{
	return top_ == 0;
}

template<class T>
inline T StackArray<T>::peek()
{
	return array_[top_ - 1];
}
