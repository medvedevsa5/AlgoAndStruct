#ifndef _COMMANDER_
#define _COMMANDER_

#include <functional>
#include <memory>
#include "Geometry.h"



class Commander
{
public:
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
	double countEven();
	double countOdd();
	double countNum(int vertexCount);
	//Дублирует всякое вхождение указанной в параметре фигуры.
	int echo(Polygon& polygon);
	int maxSeq(Polygon& polygon);
#pragma endregion

private:
	std::vector<Polygon>* polygons_;


};

#endif // _COMMANDER_