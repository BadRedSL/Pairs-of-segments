#pragma once

#include <random>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <set>
#include <unordered_map>
#include <string>

#include "Class_segment.h"

struct Point
{
public:

    double x;
    double y;
    bool side;
    Segment segment;

    Point();
    Point(const double x, const double y, const bool side, const Segment segment);
    void setPoint(const double x, const double y, const bool side, const Segment segment);

    friend bool operator< (const Point& a, const Point& b);

    friend bool operator> (const Point& a, const Point& b);
};


