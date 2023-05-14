#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

#include "Geometry.h"
#include "ErrorHandler.h"
#include "IOProcessor.h"

int main(int argc, char ** argv)
{
	//if (argc != 2)
	//{
	//	terminate(ErrorType::ArgumentError);
	//}
	
	std::vector<Polygon> poly;

	std::istringstream ss("3 (0,0) (1,0) \n4 (0,0) (0,1) (1,1) (1,0)");
	
	while (!ss.eof())
	{
		std::copy(
			std::istream_iterator<Polygon>(ss),
			std::istream_iterator<Polygon>(),
			std::back_inserter(poly)
		);

		if (ss.fail() && !ss.eof())
		{
			ss.clear();
			ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "ERROR: invalid input!" << std::endl;
		}
	}

	std::cout << std::boolalpha << ss.good();

	for (auto polygon : poly)
	{
		std::cout << getArea(polygon);
	}

	//std::copy(poly.cbegin(), poly.cend(), std::ostream_iterator<Polygon>(std::cout, "\n" ));

    return 0;
}

