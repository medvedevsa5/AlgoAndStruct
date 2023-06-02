#pragma once
#ifndef _ERROR_HANDLER_
#define _ERROR_HANDLER_

enum ErrorType
{
	ArgumentError = 1,
	FileNotOpenError,
	PolygonError,
	CommandError
};

void terminate(ErrorType&& error);
void printError(ErrorType&& error);

#endif // _ERROR_HANDLER_