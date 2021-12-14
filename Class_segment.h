#pragma once

#include <utility>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <set>
#include <unordered_map>
#include <string>


class Segment
{
public:

	/*характеризует точку начала отрезка*/

	std::pair<double, double> segmentBegin;

	/*характеризует точку конца отрезка*/

	std::pair<double, double> segmentEnd;

	Segment(const double x1 = 0.0, const double y1 = 0.0, const double x2 = 0.0, const double y2 = 0.0);

	/*методы получения доступа к координатам начала отрезка*/

	double GetX1() const;
	double GetY1() const;

	/*методы получения доступа к координатам конца отрезка*/

	double GetX2() const;
	double GetY2() const;

	/*методы устанавливающие значения координат начала отрезка*/

	void SetX1(const double value);
	void SetY1(const double value);

	/*методы устанавливающие значения координат конца отрезка*/

	void SetX2(const double value);
	void SetY2(const double value);

	/*метод, выводящий значения концов отрезка в консоль*/

	void printSegment() const;

	friend std::ostream& operator << (std::ostream& out, Segment& a);

};

