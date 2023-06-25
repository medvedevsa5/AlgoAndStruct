#ifndef _COMMANDER_
#define _COMMANDER_

#include "Geometry.h"

class Commander
{
public:
	// https://learn.microsoft.com/ru-ru/cpp/cpp/noexcept-cpp
	Commander() noexcept;
	Commander(const std::vector<Polygon>& vec);

	Commander(const Commander& src) = delete;
	Commander(Commander&& src) = delete;

	Commander operator=(const Commander& src) = delete;
	Commander operator=(Commander&& src) = delete;

	~Commander() noexcept;

	std::vector<Polygon> getVector();
	void setVector(const std::vector<Polygon>& polygons);

#pragma region COMMANDS
	double areaEven();
	double areaOdd();
	double areaMean();
	double areaNum(int vertexCount);
	double maxArea();
	double maxVertexes();
	double minArea();
	double minVertexes();
	size_t countEven();
	size_t countOdd();
	size_t countNum(int vertexCount);
	//Дублирует всякое вхождение указанной в параметре фигуры.
	size_t echo(const Polygon& polygon);
	size_t maxSeq(const Polygon& polygon);
#pragma endregion

private:
	std::vector<Polygon> polygons_;
};

#endif // _COMMANDER_