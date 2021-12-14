#include "Class_point_of_segment.h"
#include "Class_segment.h"

Point::Point()
{
    x = 0;
    y = 0;
    side = false;
}

Point::Point(const double x, const double y, const bool side, const Segment segment)
{
    this->x = x;
    this->y = y;
    this->side = side;
    this->segment = segment;
}

void Point::setPoint(const double x, const double y, const bool side, const Segment segment)
{
    this->x = x;
    this->y = y;
    this->side = side;
    this->segment = segment;
}

bool operator<(const Point& a, const Point& b)
{
    return (a.x < b.x);
}

bool operator>(const Point& a, const Point& b)
{
    return a.x > b.x;
}
