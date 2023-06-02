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

	double area = std::accumulate(polygon.points.cbegin() + 2, polygon.points.cend(), 0.0,
		std::bind(
			[&secondPoint](double& sum, const Point& thirdPoint, const auto& firstPoint)
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
					
			}, _1, _2, firstPoint)
	);

	return area;
}

#undef X
#undef Y
#undef DIMENSION