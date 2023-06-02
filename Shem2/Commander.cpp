#include "Commander.h"
#include <algorithm>
#include <numeric>
#include <iostream>

Commander::Commander() : 
	polygons_(nullptr)
{}

Commander::Commander(const std::vector<Polygon>& vec)
{
	polygons_ = new std::vector<Polygon>(vec);
}

Commander::~Commander()
{
	delete polygons_;
}

std::vector<Polygon> Commander::getVector()
{
	return std::vector<Polygon>(*polygons_);
}

void Commander::setVector(const std::vector<Polygon>& polygons)
{
	polygons_ = new std::vector<Polygon>(polygons);
}

double Commander::areaEven()
{
	if (polygons_ == nullptr)
	{
		return 0;
	}
	return std::accumulate(polygons_->cbegin(), polygons_->cend(), 0.0,
		[](double sum, const Polygon& curr)
		{
			int vertexCount = curr.points.size();
			return sum + ((vertexCount % 2 == 0) ? getArea(curr) : 0);
		}
	);;
}

double Commander::areaOdd()
{
	if (polygons_ == nullptr)
	{
		return 0;
	}

	return std::accumulate(polygons_->cbegin(), polygons_->cend(), 0.0,
		[](double sum, const Polygon& curr)
		{
			int vertexCount = curr.points.size();
			return sum + ((vertexCount % 2 != 0) ? getArea(curr) : 0);
		}
	);;
}

double Commander::areaMean()
{
	if (polygons_ == nullptr || polygons_->size() == 0)
	{
		return 0;
	}
	int polygonCount = polygons_->size();
	return std::accumulate(polygons_->cbegin(), polygons_->cend(), 0.0,
		[&polygonCount](double sum, const Polygon& curr)
		{
			return sum + (getArea(curr) / polygonCount);
		});
}

double Commander::areaNum(int vertexCount)
{
	auto polygonsWithVertexCount = std::accumulate(polygons_->cbegin(), polygons_->cend(), std::vector<Polygon>(),
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
	auto maxElement = std::max_element(polygons_->cbegin(), polygons_->cend(), 
		[](const Polygon& left, const Polygon& right)
		{
			return getArea(left) < getArea(right);
		}
	);
	return getArea(*maxElement);
}

double Commander::maxVertexes()
{
	auto maxElement = std::max_element(polygons_->cbegin(), polygons_->cend(),
		[](const Polygon& left, const Polygon& right)
		{
			return left.points.size() < left.points.size();
		}
	);
	return getArea(*maxElement);
}

double Commander::minArea()
{
	auto minElement = std::min_element(polygons_->cbegin(), polygons_->cend(),
		[](const Polygon& left, const Polygon& right)
		{
			return getArea(left) < getArea(right);
		}
	);
	return getArea(*minElement);
}

double Commander::minVertexes()
{
	auto minElement = std::min_element(polygons_->cbegin(), polygons_->cend(),
		[](const Polygon& left, const Polygon& right)
		{
			return left.points.size() < left.points.size();
		}
	);
	return getArea(*minElement);
}

double Commander::countEven()
{
	return std::count_if(polygons_->cbegin(), polygons_->cend(), 
		[](const Polygon& polygon) 
		{
			return polygon.points.size() % 2 == 0;
		}
	);
}

double Commander::countOdd()
{
	return std::count_if(polygons_->cbegin(), polygons_->cend(),
		[](const Polygon& polygon)
		{
			return !polygon.points.size() % 2 == 0;
		}
	);
}

double Commander::countNum(int vertexCount)
{
	return std::count_if(polygons_->cbegin(), polygons_->cend(),
		[&vertexCount](const Polygon& polygon)
		{
			return polygon.points.size() == vertexCount;
		}
	);
}

int Commander::echo(Polygon& polygon)
{
	using namespace std::placeholders;

	auto compare = std::bind(
		[](const Polygon& left, const Polygon& right )
		{
			int sizeDiff = left.points.size() - right.points.size();
			if (sizeDiff != 0)
			{
				return false;
			}
			else
			{
				auto rightIterator= right.points.cbegin();
				int equalCount = std::count_if(left.points.cbegin(), left.points.cend(),
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
		},
		_1, polygon);

	int count = 0;

	auto result = std::accumulate(polygons_->cbegin(), polygons_->cend(), new std::vector<Polygon>(), 
		[&count, &compare](std::vector<Polygon>* vec, const Polygon& curr) 
		{
			vec->push_back(curr);
			if (compare(curr))
			{
				count++;
				vec->push_back(curr);
			}
			return vec;
		}
	);

	delete polygons_;
	polygons_ = result;

	return count;
}

int Commander::maxSeq(Polygon& polygon)
{
	using namespace std::placeholders;

	auto compare = std::bind(
		[](const Polygon& left, const Polygon& right)
		{
			int sizeDiff = left.points.size() - right.points.size();
			if (sizeDiff != 0)
			{
				return false;
			}
			else
			{
				auto rightIterator = right.points.cbegin();
				int equalCount = std::count_if(left.points.cbegin(), left.points.cend(),
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
		},
		_1, polygon);

	int maxLength = 0;
	int counter = 0;

	return std::accumulate(polygons_->cbegin(), polygons_->cend(), 0,
			[&compare, &maxLength, &counter](int seqLength, const Polygon& right)
			{
				bool isEqual = compare(right);
				if (isEqual)
				{
					++counter;
					maxLength = counter > maxLength ? counter : maxLength;
				}
				else
				{
					counter = 0;
				}
				return maxLength;
			}
	);
}
