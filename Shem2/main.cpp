#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iomanip>

#include "Geometry.h"
#include "IOProcessor.h"
#include "ErrorHandler.h"
#include "Commander.h"

std::vector<Polygon> readStream(std::istream& in);
std::vector<Polygon> handleCommands(std::istream& in, std::ostream& out, const std::vector<Polygon>& vec);
void writeResult(std::ostream& out, std::vector<Polygon>& vec);

int main()
{
	std::string input;

	std::cout << "Enter polygon input file.\n";
	std::cin >> input;
	std::ifstream polygonInputStream(input);

	std::cout << "Enter command input file.\n";
	std::cin >> input;
	std::ifstream commandInputStream(input);

	std::ofstream polygonOutputStream("polygon_output.txt");
	std::ofstream commandOutputStream("command_output.txt");

	if (
		!polygonInputStream	  ||
		!commandInputStream	  ||
		!polygonOutputStream  ||
		!commandOutputStream )
	{
		std::cerr << "IO error.";
		return -1;
	}

	std::vector<Polygon> inputVector = readStream(polygonInputStream);
	std::vector<Polygon> resultVector = handleCommands(commandInputStream, commandOutputStream, inputVector);
	writeResult(polygonOutputStream, resultVector);

	polygonInputStream.close();
	commandInputStream.close();
	polygonOutputStream.close();
	commandOutputStream.close();

	return 0;
}

std::vector<Polygon> readStream(std::istream& in)
{
	std::vector<Polygon> polygons;

	while (!in.eof())
	{
		std::copy(
			std::istream_iterator<Polygon>(in),
			std::istream_iterator<Polygon>(),
			std::back_inserter(polygons)
		);

		if (in.fail() && !in.eof())
		{
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printError(ErrorType::PolygonError);
		}
	}

	return polygons;
}

std::vector<Polygon> handleCommands(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
{
	Commander cmd(polygons);
	ScopeGuard scopeGuard(in);

	out << std::fixed << std::setprecision(1);

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
				bool isDigit = std::all_of(type.cbegin() + 1, type.cend(), std::isdigit);
				if (!isDigit)
				{ 
					printError(ErrorType::ArgumentError);
					continue;
				}
				int arg = std::stoi(type);
				out << cmd.areaNum(arg);
			}
			else
			{
				printError(ErrorType::CommandError);
				continue;
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
				continue;
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
				continue;
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
				bool isDigit = std::all_of(type.cbegin() + 1, type.cend(), std::isdigit);
				if (!isDigit)
				{
					printError(ErrorType::ArgumentError);
					continue;
				}
				int arg = std::stoi(type);
				out << cmd.countNum(arg);
			}
			else
			{
				printError(ErrorType::CommandError);
				continue;
			}
		}
		else if (command == "MAXSEQ")
		{
			in >> inputPolygon;
			if (in)
			{
				out << cmd.maxSeq(inputPolygon);
			}
		}
		else if (command == "ECHO")
		{
			in >> inputPolygon;
			if (in)
			{
				out << cmd.echo(inputPolygon);
			}
		}
		else if (command.empty())
		{
			continue;
		}
		else
		{
			printError(ErrorType::CommandError);
			continue;
		}

		if (in.fail() && !in.eof())
		{
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printError(ErrorType::ArgumentError);
			continue;
		}

		out << '\n';
	}

	return cmd.getVector();
}

void writeResult(std::ostream& out, std::vector<Polygon>& vec)
{
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<Polygon>(out, "\n"));
}