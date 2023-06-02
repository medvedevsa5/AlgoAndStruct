#include <iostream>
#include "ErrorHandler.h"

void terminate(ErrorType&& error)
{
	printError(std::move(error));
	exit(error);
}

void printError(ErrorType&& error)
{
	std::string errorString = "";
	switch (error)
	{
	case ArgumentError:
		errorString = "Usage: programm.exe <PATH_TO_FILE>.";
		break;
	case FileNotOpenError:
		errorString = "File can not be open.";
		break;
	case CommandError:
		errorString = "<INVALID COMMAND>";
		break;
	default:
		errorString = "Unknown error.";
		break;
	}

	std::cerr << '\n' << errorString << '\n';
}

