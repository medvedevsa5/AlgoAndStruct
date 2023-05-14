#pragma once

class QueueOverflowException : public std::exception
{
public:
	const char* what() const override
	{
		return "Queue Overflow!";
	}
};

class QueueUnderflowException : public std::exception
{
public:
	const char* what() const override
	{
		return "Queue Underflow!";
	}
};