#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "Geometry.h"
#include "IOProcessor.h"
#include "ErrorHandler.h"
#include "Commander.h"

std::vector<Polygon> readStream(std::istream& in);
std::vector<Polygon> handleCommands(std::istream& in, std::ostream& out, std::vector<Polygon>& vec);
void writeResult(std::ostream& out, std::vector<Polygon>& vec);

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		terminate(ErrorType::ArgumentError);
	}
	
	std::ifstream fileStream(argv[1]);
	if (!fileStream.is_open())
	{
		terminate(ErrorType::FileNotOpenError);
	}

	std::vector<Polygon> input = readStream(fileStream);
	std::vector<Polygon> result = handleCommands(std::cin, std::cout, input);
	writeResult(std::cout, result);

	return 0;
}

std::vector<Polygon> readStream(std::istream& in)
{
	std::vector<Polygon> poly;

	while (!in.eof())
	{
		std::copy(
			std::istream_iterator<Polygon>(in),
			std::istream_iterator<Polygon>(),
			std::back_inserter(poly)
		);

		if (in.fail() && !in.eof())
		{
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printError(ErrorType::PolygonError);
		}
	}

	return poly;
}

std::vector<Polygon> handleCommands(std::istream& in, std::ostream& out, std::vector<Polygon>& vec)
{
	Commander cmd(vec);
	while (!in.eof())
	{
		std::string command = "";
		std::string type = "";
		Polygon inputPolygon = {};

		in >> command;
		if (command == "AREA")
		{
			in >> type;
			if (type == "EVEN")
			{
				out << cmd.areaEven();
			}
			else if (type == "ODD")
			{
				out << cmd.areaOdd();
			}
			else if (type == "MEAN")
			{
				out << cmd.areaMean();
			}
			else if (std::isdigit(type[0]))
			{
				bool isDigit = std::all_of(type.cbegin(), type.cend(),
					[](const char& ch)
					{
						return std::isdigit(ch);
					}
				);
				if (isDigit)
				{ 
					int arg = std::stoi(type);
					out << cmd.areaNum(arg);
				}
			}
			else
			{
				printError(ErrorType::CommandError);
			}
		}
		else if (command == "MAX")
		{
			in >> type;
			if (type == "AREA")
			{
				out << cmd.maxArea();
			}
			else if (type == "VERTEXES")
			{
				out << cmd.maxVertexes();
			}
			else
			{
				printError(ErrorType::CommandError);
			}
		}
		else if (command == "MIN")
		{
			in >> type;
			if (type == "AREA")
			{
				out << cmd.minArea();
			}
			else if (type == "VERTEXES")
			{
				out << cmd.minVertexes();
			}
			else
			{
				printError(ErrorType::CommandError);
			}
		}
		else if (command == "COUNT")
		{
			in >> type;
			if (type == "EVEN")
			{
				out << cmd.countEven();
			}
			else if (type == "ODD")
			{
				out << cmd.countOdd();
			}
			else if (isdigit(type[0]))
			{
				size_t pos = 0;
				int arg = std::stoi(type, &pos, 10);
				if (pos != type.length())
				{
					printError(ErrorType::CommandError);
					continue;
				}
				out << cmd.countNum(arg);
			}
			else
			{
				printError(ErrorType::CommandError);
			}
		}
		else if (command == "MAXSEQ")
		{
			in >> inputPolygon;
			if (!in)
			{
				break;
			}
			out << cmd.maxSeq(inputPolygon);
		}
		else if (command == "ECHO")
		{
			in >> inputPolygon;
			if (!in)
			{
				break;
			}
			out << cmd.echo(inputPolygon);
		}
		else if (command.empty())
		{}
		else
		{
			printError(ErrorType::CommandError);
		}
		out << std::endl;
	}

	return cmd.getVector();
}

void writeResult(std::ostream& out, std::vector<Polygon>& vec)
{
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<Polygon>(out, "\n"));
}