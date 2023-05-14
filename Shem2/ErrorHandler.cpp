#include <iostream>

#include "ErrorHandler.h"

void terminate(ErrorType error)
{
	std::string errorString = "";

	switch (error)
	{
	case ArgumentError:
		errorString = "Usage: programm.exe <PATH_TO_FILE>.";
		break;
	case InputError:
		errorString = "Error: wrong input.";
		break;
	default: 
		errorString = "Unknown error.";
		break;
	}

	std::cerr << errorString << std::endl;
	exit(error);
}
