#pragma once

#include <vector>

#include "Class_segment.h"





class SetOfSegments
{
public:

	/*характеризует множество отрезков*/

	std::vector<Segment> segmentSet;

	/*характеризует количество отрезков в множестве*/

	long long counter;

	/*характеризует время работы наивного алгоритма*/

	double nativeTime;

	/*характеризует время работы эффективного алгоритма*/

	double effectiveTime;

	/*метод, определяющий знак скалярного произведения векторов с общим началом*/

	double direction(const Segment &a, const Segment &b) const;

	/*метод, определяющий наложение векторов с общим началом*/

	bool onSegment(const Segment& a, const Segment& b) const;

	SetOfSegments(const std::vector<Segment> &vector);

	SetOfSegments();

	~SetOfSegments();

	/*метод, добавляющий отрезок в множество*/

	void addSegment(const Segment &newSegment);

	/*метод, проверяющий пересечение отрезков множества на основе (2, 3) - дерева*/

	bool effectiveIntersection();

	/*метод, делающий наивную проверку пересечения отрезков множества*/

	bool intersection();

	/*автоматическая генерация множества из n отрезков на единичном квадрате*/

	void autoGenerator(const long n, const long k = 0);

	/*автоматическая генерация множества из n отрезков длины r на единичном квадрате*/

	void autoRGenerator(const long n, const std::vector<double> r);

	/*ручной генерация множества из n отрезков*/

	void handGenerator();

	/*вывод в консоль всех отрезков множества*/

	void printSetOfSegments() const;

	/*Проверяет пересечение 2-х отрезков*/

	bool twoSegmentIntersection(const Segment& a, const Segment& b) const;

	/*Очищает сожержимое множества отрезков*/

	void clear();

	double getNativeTime() const;

	double getEffectiveTime() const;

	friend bool operator< (const Segment& a, const Segment& b);

	friend bool operator> (const Segment& a, const Segment& b);

};


// A point in 2D plane
struct nPoint
{
	double x, y;
};

// A line segment with left as Point
// with smaller x value and right with
// larger x value.
struct nSegment
{
	nPoint left, right;
};


// An event for sweep line algorithm
// An event has a point, the position
// of point (whether left or right) and
// index of point in the original input
// array of segments.
struct Event {
	double x, y;
	bool isLeft;
	int index;
	Event(double x, double y, bool l, int i) : x(x), y(y), isLeft(l), index(i) {}

	// This is for maintaining the order in set.
	bool operator<(const Event& e) const {
		if (y == e.y)return x < e.x;
		return y < e.y;
	}
};

bool onSegment(std::pair<double, double> p, std::pair<double, double> q, std::pair<double, double> r);
int orientation(std::pair<double, double> p, std::pair<double, double> q, std::pair<double, double> r);
bool doIntersect(Segment s1, Segment s2);
std::set<Event>::iterator pred(std::set<Event>& s, std::set<Event>::iterator it);
std::set<Event>::iterator succ(std::set<Event>& s, std::set<Event>::iterator it);
int isIntersect(std::vector<Segment>& arr, int n, double& time);