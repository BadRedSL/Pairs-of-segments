#include "Class_segment.h"


Segment::Segment(const double x1, const double y1, const double x2, const double y2)
{
	segmentBegin.first = x1;
	segmentBegin.second = y1;

	segmentEnd.first = x2;
	segmentEnd.second = y2;

}

double Segment::GetX1() const
{
	return segmentBegin.first;
}

double Segment::GetY1() const
{
	return segmentBegin.second;
}

double Segment::GetX2() const
{
	return segmentEnd.first;
}

double Segment::GetY2() const
{
	return segmentEnd.second;
}


void Segment::SetX1(const double x1)
{
	segmentBegin.first = x1;
}

void Segment::SetY1(const double y1)
{
	segmentBegin.second = y1;
}

void Segment::SetX2(const double x2)
{
	segmentEnd.first = x2;
}

void Segment::SetY2(const double y2)
{
	segmentEnd.second = y2;
}

void Segment::printSegment() const
{
	std::cout << "[ (" << GetX1() << "; " << GetY1() << ") ; " << "(" << GetX2() << "; " << GetY2() << ") ]" << std::endl;
}

std::ostream& operator<<(std::ostream& out, Segment& a)
{
	out << "[ (" << a.GetX1() << "; " << a.GetY1() << ") ; " << "(" << a.GetX2() << "; " << a.GetY2() << ") ]";

	return out;
}
