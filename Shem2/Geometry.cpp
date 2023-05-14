#include "Geometry.h"

#define X 0
#define Y 1
#define DIMENSION 2

double getArea(const Polygon& polygon)
{
	double area = 0;

	size_t pointCount = polygon.points.size();
	if (pointCount == 0)
	{
		throw std::exception("Polygon with 0 point exception");
	}
	Point firstPoint = polygon.points[0];

	for (size_t i = 0; i < pointCount - 2; i++)
	{
		Point secondPoint = polygon.points[i + 1];
		Point thirdPoint = polygon.points[i + 2];

		int firstVector[DIMENSION]
		{
			secondPoint.x - firstPoint.x,
			secondPoint.y - firstPoint.y
		};
		int secondVector[DIMENSION]
		{
			thirdPoint.x - firstPoint.x,
			thirdPoint.y - firstPoint.y
		};

		area += 0.5 * std::abs(
			firstVector[X] * secondVector[Y] -
			firstVector[Y] * secondVector[X]
		);
	}

	return area;
}

#undef X
#undef Y
#undef DIMENSION