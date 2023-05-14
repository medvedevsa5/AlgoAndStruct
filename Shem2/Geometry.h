#pragma once

#include <vector>

struct Point
{
	int x, y;
};

struct Polygon
{
	std::vector< Point > points;
};

double getArea(const Polygon& polygon);
