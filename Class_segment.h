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

	/*������������� ����� ������ �������*/

	std::pair<double, double> segmentBegin;

	/*������������� ����� ����� �������*/

	std::pair<double, double> segmentEnd;

	Segment(const double x1 = 0.0, const double y1 = 0.0, const double x2 = 0.0, const double y2 = 0.0);

	/*������ ��������� ������� � ����������� ������ �������*/

	double GetX1() const;
	double GetY1() const;

	/*������ ��������� ������� � ����������� ����� �������*/

	double GetX2() const;
	double GetY2() const;

	/*������ ��������������� �������� ��������� ������ �������*/

	void SetX1(const double value);
	void SetY1(const double value);

	/*������ ��������������� �������� ��������� ����� �������*/

	void SetX2(const double value);
	void SetY2(const double value);

	/*�����, ��������� �������� ������ ������� � �������*/

	void printSegment() const;

	friend std::ostream& operator << (std::ostream& out, Segment& a);

};

