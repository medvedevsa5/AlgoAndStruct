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
		errorString = "<INVALID COMMAND ARGUMENT>";
		break;
	case PolygonError:
		errorString = "<INVALID POLYGON>";
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

