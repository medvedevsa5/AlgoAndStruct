#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>

#include "Geometry.h"

#define X 0
#define Y 1
#define DIMENSION 2

double TriangleArea::operator()(const Point& a, const Point& b, const Point& c)
{
	int firstVector[DIMENSION]
	{
		b.x - a.x,
		b.y - a.y
	};
	int secondVector[DIMENSION]
	{
		c.x - a.x,
		c.y - a.y
	};
	return 0.5 * std::abs(
		firstVector[X] * secondVector[Y] -
		firstVector[Y] * secondVector[X]
	);
}


double getArea(const Polygon& polygon)
{
	using namespace std::placeholders;
	
	auto firstPoint = polygon.points.cbegin();
	auto secondPoint = polygon.points.cbegin() + 1;

	auto bindedAreaFunc = std::bind(TriangleArea(), *firstPoint, _1, _2);

	double area = std::accumulate(polygon.points.cbegin() + 2, polygon.points.cend(), 0.0,
		[&bindedAreaFunc, &secondPoint](double& sum, const Point& currPoint)
		{
			sum += bindedAreaFunc(*secondPoint, currPoint);
			++secondPoint;
			return sum;
		}
	);

	return area;
}

bool operator==(const Polygon& left, const Polygon& right)
{
	if (left.points.size() != right.points.size())
	{
		return false;
	}
	else
	{
		auto rightIterator = right.points.cbegin();
		size_t equalCount = std::count_if(left.points.cbegin(), left.points.cend(),
			[&rightIterator](const Point& leftPoint)
			{
				bool isEqual =
					leftPoint.x == rightIterator->x &&
					leftPoint.y == rightIterator->y;
				++rightIterator;
				return isEqual;
			}
		);
		return equalCount == left.points.size();
	}
}

#undef X
#undef Y
#undef DIMENSION

