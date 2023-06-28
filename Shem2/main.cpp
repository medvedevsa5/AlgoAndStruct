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
	if (!polygonInputStream)
	{
		std::cerr << "Error opening polygon input file";
		return -1;
	}

	std::cout << "Enter command input file.\n";
	std::cin >> input;
	std::ifstream commandInputStream(input);
	if (!polygonInputStream)
	{
		std::cerr << "Error opening command input file";
		return -2;
	}

	std::ofstream polygonOutputStream("polygon_output.txt");
	std::ofstream commandOutputStream("command_output.txt");
	if (!polygonOutputStream || !commandOutputStream)
	{
		std::cerr << "Error opening one of the output files.";
		return -3;
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
				out << "AREA EVEN: " << cmd.areaEven();
			}
			else if (type == "ODD")
			{
				out << "AREA ODD: " << cmd.areaOdd();
			}
			else if (type == "MEAN")
			{
				out << "AREA MEAN: " << cmd.areaMean();
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
				out << "AREA " << arg << ": " << cmd.areaNum(arg);
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
				out << "MAX AREA: " << cmd.maxArea();
			}
			else if (type == "VERTEXES")
			{
				out << "MAX VERTEXES: " << cmd.maxVertexes();
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
				out << "MIN AREA: " << cmd.minArea();
			}
			else if (type == "VERTEXES")
			{
				out << "MIN VERTEXES: " << cmd.minVertexes();
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
				out << "COUNT EVEN: " << cmd.countEven();
			}
			else if (type == "ODD")
			{
				out << "COUNT ODD: " << cmd.countOdd();
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
				out << "COUNT ODD " << arg << ": " << cmd.countNum(arg);
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
				out << "MAXSEQ " << inputPolygon << ": " << cmd.maxSeq(inputPolygon);
			}
		}
		else if (command == "ECHO")
		{
			in >> inputPolygon;
			if (in)
			{
				out << "ECHO " << inputPolygon << ": " << cmd.echo(inputPolygon);
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