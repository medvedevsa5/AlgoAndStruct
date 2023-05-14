#pragma once
#include "Queue.h"
#include "QueueExceptions.h"

template<class T>
class QueueArray : public Queue<T>
{
private:
	T* array_ = nullptr;
	size_t head_ = 0;
	size_t tail_ = 0;
	size_t size_ = 0;
	size_t amount_ = 0;

public:
	QueueArray(size_t size = 128);
	~QueueArray();

	QueueArray(const QueueArray<T>& src) = delete;
	QueueArray(QueueArray<T>&& src) = delete;
	QueueArray& operator=(const QueueArray<T>& src) = delete;
	QueueArray& operator=(const QueueArray<T>&& src) = delete;

	void enQueue(const T& e) override;
	T deQueue() override;
	bool isEmpty() override;
};

template<class T>
inline QueueArray<T>::QueueArray(size_t size)
{
	this->size_ = size;
	this->amount_ = 0;
	this->tail_ = 0;
	this->head_ = 0;
	this->array_ = new T[size]{};
}

template<class T>
inline QueueArray<T>::~QueueArray()
{
	delete array_;
}


template<class T>
inline void QueueArray<T>::enQueue(const T& e)
{
	if (amount_ == size_)
	{
		throw QueueOverflowException();
	}
	array_[tail_] = e;
	if (tail_ + 1 == size_)
	{
		tail_ = 0;
	}
	else
	{
		tail_ += 1;
	}
	amount_ += 1;
}

template<class T>
inline T QueueArray<T>::deQueue()
{
	if (amount_ == 0)
	{
		throw QueueUnderflowException();
	}
	T tmp = array_[head_];
	if (head_ + 1 == size_)
	{
		head_ = 0;
	}
	else
	{
		head_ += 1;
	}
	amount_ -= 1;
	return tmp;
}

template<class T>
inline bool QueueArray<T>::isEmpty()
{
	return amount_ == 0;
}
