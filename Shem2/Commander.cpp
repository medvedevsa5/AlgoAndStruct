#include "Commander.h"
#include "Geometry.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>

Commander::Commander() noexcept
{}

Commander::Commander(const std::vector<Polygon>& polygons) :
	polygons_(polygons)
{}

Commander::~Commander()
{}

std::vector<Polygon> Commander::getVector()
{
	return polygons_;
}

void Commander::setVector(const std::vector<Polygon>& polygons)
{
	polygons_ = polygons;
}

double Commander::areaEven()
{
	return std::accumulate(polygons_.cbegin(), polygons_.cend(), 0.0,
		[](double sum, const Polygon& curr)
		{
			size_t vertexCount = curr.points.size();
			return sum + ((vertexCount % 2 == 0) ? getArea(curr) : 0);
		}
	);
}

double Commander::areaOdd()
{
	return std::accumulate(polygons_.cbegin(), polygons_.cend(), 0.0,
		[](double sum, const Polygon& curr)
		{
			size_t vertexCount = curr.points.size();
			return sum + ((vertexCount % 2 != 0) ? getArea(curr) : 0);
		}
	);
}

double Commander::areaMean()
{
	if (polygons_.size() == 0)
	{
		return 0;
	}
	size_t polygonCount = polygons_.size();
	return std::accumulate(polygons_.cbegin(), polygons_.cend(), 0.0,
		[&polygonCount](double sum, const Polygon& curr)
		{
			return sum + (getArea(curr) / polygonCount);
		});
}

double Commander::areaNum(int vertexCount)
{
	auto polygonsWithVertexCount = std::accumulate(polygons_.cbegin(), polygons_.cend(), std::vector<Polygon>(),
		[&vertexCount](std::vector<Polygon>& vec, const Polygon& polygon) 
		{
			if (polygon.points.size() == vertexCount)
			{
				vec.push_back(polygon);
			}
			return vec;
		}
	);

	double area = std::accumulate(polygonsWithVertexCount.cbegin(), polygonsWithVertexCount.cend(), 0.0,
		[](double currArea, const Polygon& polygon)
		{
			return currArea + getArea(polygon);
		}
	);

	return area;
}

double Commander::maxArea()
{
	auto maxElement = std::max_element(polygons_.cbegin(), polygons_.cend(),
		[](const Polygon& left, const Polygon& right)
		{
			return getArea(left) < getArea(right);
		}
	);
	return getArea(*maxElement);
}

double Commander::maxVertexes()
{
	auto maxElement = std::max_element(polygons_.cbegin(), polygons_.cend(),
		[](const Polygon& left, const Polygon& right)
		{
			return left.points.size() < left.points.size();
		}
	);
	return getArea(*maxElement);
}

double Commander::minArea()
{
	auto minElement = std::min_element(polygons_.cbegin(), polygons_.cend(),
		[](const Polygon& left, const Polygon& right)
		{
			return getArea(left) < getArea(right);
		}
	);
	return getArea(*minElement);
}

double Commander::minVertexes()
{
	auto minElement = std::min_element(polygons_.cbegin(), polygons_.cend(),
		[](const Polygon& left, const Polygon& right)
		{
			return left.points.size() < left.points.size();
		}
	);
	return getArea(*minElement);
}

size_t Commander::countEven()
{
	return std::count_if(polygons_.cbegin(), polygons_.cend(),
		[](const Polygon& polygon) 
		{
			return polygon.points.size() % 2 == 0;
		}
	);
}

size_t Commander::countOdd()
{
	return std::count_if(polygons_.cbegin(), polygons_.cend(),
		[](const Polygon& polygon)
		{
			return polygon.points.size() % 2 != 0;
		}
	);
}

size_t Commander::countNum(int vertexCount)
{
	return std::count_if(polygons_.cbegin(), polygons_.cend(),
		[&vertexCount](const Polygon& polygon)
		{
			return polygon.points.size() == vertexCount;
		}
	);
}

size_t Commander::echo(const Polygon& polygon)
{
	using namespace std::placeholders;

	auto equalToParam = std::bind(std::equal_to<Polygon>(), polygon, _1);

	int count = 0;

	size_t matches = std::count(polygons_.cbegin(), polygons_.cend(), polygon);

	auto result = std::accumulate(polygons_.cbegin(), polygons_.cend(), std::vector<Polygon>(polygons_.size() + matches),
		[&equalToParam, &count](std::vector<Polygon>& result, const Polygon& current)
		{
			result.push_back(current);
			if (equalToParam(current))
			{
				count++;
				result.push_back(current);
			}
			return result;
		}
	);

	polygons_.swap(result);

	return count;
}

size_t Commander::maxSeq(const Polygon& polygon)
{
	using namespace std::placeholders;

	auto equalToParam = std::bind(std::equal_to<Polygon>(), polygon, _1);

	int maxLength = 0;
	int counter = 0;

	return std::accumulate(polygons_.cbegin(), polygons_.cend(), 0,
			[&equalToParam, &maxLength, &counter](int seqLength, const Polygon& right)
			{
				if (equalToParam(right))
				{
					++counter;
					maxLength = (counter > maxLength) ? counter : maxLength;
				}
				else
				{
					counter = 0;
				}
				return maxLength;
			}
	);
}
