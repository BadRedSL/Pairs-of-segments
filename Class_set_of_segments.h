#pragma once

#include <vector>

#include "Class_segment.h"





struct SetOfSegments
{
public:

	/*������������� ��������� ��������*/

	std::vector<Segment> segmentSet;

	/*������������� ���������� �������� � ���������*/

	long long counter;

	/*������������� ����� ������ �������� ���������*/

	double nativeTime;

	/*������������� ����� ������ ������������ ���������*/

	double effectiveTime;

	/*�����, ������������ ���� ���������� ������������ �������� � ����� �������*/

	double direction(const Segment &a, const Segment &b) const;

	/*�����, ������������ ��������� �������� � ����� �������*/

	bool onSegment(const Segment& a, const Segment& b) const;

	SetOfSegments(const std::vector<Segment> &vector);

	SetOfSegments();

	~SetOfSegments();

	/*�����, ����������� ������� � ���������*/

	void addSegment(const Segment &newSegment);

	/*�����, ����������� ����������� �������� ��������� �� ������ (2, 3) - ������*/

	bool effectiveIntersection();

	/*�����, �������� ������� �������� ����������� �������� ���������*/

	bool intersection();

	/*�������������� ��������� ��������� �� n �������� �� ��������� ��������*/

	void autoGenerator(const long n, const long k = 0);

	/*�������������� ��������� ��������� �� n �������� ����� r �� ��������� ��������*/

	void autoRGenerator(const long n, const std::vector<double> r);

	/*������ ��������� ��������� �� n ��������*/

	void handGenerator();

	/*����� � ������� ���� �������� ���������*/

	void printSetOfSegments() const;

	/*��������� ����������� 2-� ��������*/

	bool twoSegmentIntersection(const Segment& a, const Segment& b) const;

	/*������� ���������� ��������� ��������*/

	void clear();

	double getNativeTime() const;

	double getEffectiveTime() const;

	friend bool operator< (const Segment& a, const Segment& b);

	friend bool operator> (const Segment& a, const Segment& b);

};
