#pragma once
#include <exception>

class StackOverflowException : public std::exception
{
public:
	const char* what() const override
 	{
		return "Stack Overflow!";
	}
};

class StackUnderflowException : public std::exception
{
public:
	const char* what() const override
	{ 
		return "Stack Underflow!";
	}
};