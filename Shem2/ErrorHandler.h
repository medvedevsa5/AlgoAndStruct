#pragma once

enum ErrorType
{
	ArgumentError = 1,
	InputError = 2
	
};

void terminate(ErrorType error);