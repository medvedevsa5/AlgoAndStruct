#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>

#include "Geometry.h"

#define X 0
#define Y 1
#define DIMENSION 2

double getArea(const Polygon& polygon)
{
	using namespace std::placeholders;
	
	auto firstPoint = polygon.points.cbegin();
	auto secondPoint = polygon.points.cbegin() + 1;
	auto thirdPoint = polygon.points.cbegin() + 2;

	double area = std::accumulate(thirdPoint, polygon.points.cend(), 0.0,
			[&firstPoint, &secondPoint](double& sum, const Point& thirdPoint)
			{
				int firstVector[DIMENSION]
				{
					secondPoint->x - firstPoint->x,
					secondPoint->y - firstPoint->y
				};
				int secondVector[DIMENSION]
				{
					thirdPoint.x - firstPoint->x,
					thirdPoint.y - firstPoint->y
				};
				sum += 0.5 * std::abs(
					firstVector[X] * secondVector[Y] -
					firstVector[Y] * secondVector[X]
				);
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