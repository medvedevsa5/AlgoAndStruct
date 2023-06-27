#pragma once
#ifndef _GEOMETRY_ 
#define _GEOMETRY_

#include <vector>

struct Point
{
	int x, y;
};

struct Polygon
{
	std::vector<Point> points;
};

class TriangleArea
{
public:
	double operator()(const Point& a, const Point& b, const Point& c);
};

bool operator==(const Polygon& left, const Polygon& right);

double getArea(const Polygon& polygon);

#endif _GEOMETRY_