#include <random>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <set>
#include <unordered_map>
#include <string>

#include "Class_set_of_segments.h"
#include "Class_segment.h"
#include "Class_2_3_tree.h"
#include "Class_point_of_segment.h"

double SetOfSegments::direction(const Segment &a, const Segment &b) const
{
	double result = (a.GetX2() - a.GetX1()) * (b.GetY2() - b.GetY1()) -
		(a.GetY2() - a.GetY1()) * (b.GetX2() - b.GetX1());

	return result;
}

bool SetOfSegments::onSegment(const Segment& a, const Segment& b) const
{
	if ((std::min(a.GetX1(), a.GetX2()) <= b.GetX2() <= std::max(a.GetX1(), a.GetX2())) &&
		(std::min(a.GetY1(), a.GetY2()) <= b.GetY2() <= std::max(a.GetY1(), a.GetY2())))
	{
		return true;
	}
	else
	{
		return false;
	}

}

SetOfSegments::SetOfSegments(const std::vector<Segment> &vector)
{
	segmentSet = vector;
	counter = vector.size();
	nativeTime = 0;
	effectiveTime = 0;
}

SetOfSegments::SetOfSegments()
{
	counter = 0;
	nativeTime = 0;
	effectiveTime = 0;
}

SetOfSegments::~SetOfSegments()
{
	segmentSet.clear();
	counter = 0;
	nativeTime = 0;
	effectiveTime = 0;
}

void SetOfSegments::addSegment(const Segment &newSegment)
{
	segmentSet.push_back(newSegment);
	++counter;
}

bool SetOfSegments::effectiveIntersection()
{
	auto start = std::chrono::system_clock::now();

	std::vector<Point> pointSet;
	bool result = false;
	std::multiset<Segment> ourTree;
	for (size_t i = 0; i < counter; ++i)
	{
		bool isLeft = (segmentSet[i].GetX1() < segmentSet[i].GetX2()) ? true : false;
		pointSet.push_back(Point(segmentSet[i].GetX1(), segmentSet[i].GetY1(), isLeft, segmentSet[i]));
		pointSet.push_back(Point(segmentSet[i].GetX2(), segmentSet[i].GetY2(), !isLeft, segmentSet[i]));
	}

	sort(pointSet.begin(), pointSet.end());

	std::set<Segment>::iterator curr;
	std::set<Segment>::iterator pred;
	std::set<Segment>::iterator next;
	Segment s, s1, s2;

	for (size_t i = 0; i < counter * 2; ++i)
	{
		if (pointSet[i].side == true)
		{
			curr = (ourTree.insert(pointSet[i].segment));
			s = (*curr);

			if (curr == ourTree.begin())
			{
				s1 = Segment(1000 + i, 0, 1000 + i, 1);
			}
			else
			{
				pred = std::prev(curr);
				s1 = (*pred);
			}
			if (std::next(curr) == ourTree.end())
			{
				s2 = Segment(5000 + i, 0, 5000 + i, 1);
			}
			else 
			{
				next = std::next(curr);
				s2 = (*next);
			}
			
			if (twoSegmentIntersection(s1, s) || twoSegmentIntersection(s2, s))
			{
				result = true;
			}
		}
		else if (pointSet[i].side == false)
		{
			if (curr == ourTree.begin())
			{
				s1 = Segment(1000 + i, 0, 1000 + i, 1);
			}
			else
			{
				pred = std::prev(curr);
				s1 = (*pred);
			}
			if (std::next(curr) == ourTree.end())
			{
				s2 = Segment(5000 + i, 0, 5000 + i, 1);
			}
			else
			{
				next = std::next(curr);
				s2 = (*next);
			}
			
			if (twoSegmentIntersection(s1, s2))
			{
				result = true;
			}
			ourTree.erase(curr);
			curr = ourTree.begin();
		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> sec = end - start;

	std::cout << "Время работы \"эффективного\" алгоритма: " << sec.count() << " сек " << std::endl;

	effectiveTime = sec.count();

	return result;
}

bool SetOfSegments::intersection() 
{
	auto start = std::chrono::system_clock::now();

	bool result = false;

	if (this->segmentSet.size() > 0)
	{

		for (size_t i = 0; i < counter - 1; ++i)
		{
			for (size_t j = i + 1; j < counter; ++j)
			{
				if (twoSegmentIntersection(segmentSet[i], segmentSet[j]))
				{
					result = true;
					//std::cout << segmentSet[i] << " и " << segmentSet[j] << " пара пересекающихся отрезков" << std::endl;
				}
			}
		}

	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> sec = end - start;

	std::cout << "Время работы \"наивного\" алгоритма: " << sec.count() << " сек " << std::endl;
	
	nativeTime = sec.count();

	return result;
}

void SetOfSegments::autoGenerator(const long n, long k)
{
	std::mt19937 randomNumber(0);
	std::uniform_real_distribution<double> urd(0, 1);
	Segment tmp;

	if (k == 0)
	{
		for (size_t i = 0; i < n; ++i)
		{
			tmp.SetX1(urd(randomNumber));
			tmp.SetY1(urd(randomNumber));
			tmp.SetX2(urd(randomNumber));
			tmp.SetY2(urd(randomNumber));

			this->addSegment(tmp);

		}
	}
	else
	{
		double interval = 0.0001;

		for (size_t i = 0; i < k; ++i)
		{
			tmp.SetX1(interval);
			tmp.SetY1(0.01);
			tmp.SetX2(interval);
			tmp.SetY2(0.5);

			this->addSegment(tmp);

			interval += interval;
		}

		for (size_t i = 0; i < 2; ++i)
		{
			tmp.SetX1(interval);
			tmp.SetY1(0.01);
			tmp.SetX2(interval);
			tmp.SetY2(i+0.05);

			//std::cout << tmp << std::endl;

			this->addSegment(tmp);
		}

		for (size_t i = (k+2); i < n; ++i)
		{
			interval += interval;

			tmp.SetX1(interval);
			tmp.SetY1(0.01);
			tmp.SetX2(interval);
			tmp.SetY2(0.5);

			this->addSegment(tmp);
			
		}

	}

}

void SetOfSegments::autoRGenerator(const long n, const std::vector<double> r)
{
	std::mt19937 randomNumber(0);
	std::uniform_real_distribution<double> urd(0, 1);

	std::mt19937 randomAngle(0);
	std::uniform_int_distribution<int> uid(0, 180);

	const double PI = 3.14159265;

	Segment tmp;

	for (size_t i = 0; i < n; ++i)
	{
		double x = urd(randomNumber);
		double y = urd(randomNumber);

		double angle = (uid(randomAngle) * PI) / 180;

		tmp.SetX1(x - (r[i] / 2 * cos(angle)));
		tmp.SetY1(y - (r[i] / 2 * sin(angle)));
		tmp.SetX2(x + (r[i] / 2 * cos(angle)));
		tmp.SetY2(y + (r[i] / 2 * sin(angle)));

		this->addSegment(tmp);

	}

}

void SetOfSegments::handGenerator()
{
	using std::cout;
	using std::cin;
	using std::endl;

	cout << "Введите желаемое количество отрезков: ";
	
	double n;


	do
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Попробуйте еще раз: ";
		}

		cin >> n;

		if (n == 0)
		{
			std::cout << "Ну и ладно..." << std::endl;
			exit(0);
		}

	} while (cin.fail());

	Segment tmp;

	long decorCounter = 1;

	double x1;
	double y1;
	double x2;
	double y2;

	for (size_t i = 0; i < n; ++i, ++decorCounter)
	{

		cout << "Введите координату Х1 " << decorCounter << "-ого отрезка: ";

		do
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "Попробуйте ввести координату Х1 " << decorCounter << "-ого отрезка еще раз: ";
			}

			cin >> x1;

		} while (cin.fail());

		tmp.SetX1(x1);

		cout << "Введите координату Y1 " << decorCounter << "-ого отрезка: ";

		do
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "Попробуйте ввести координату Y1 " << decorCounter << "-ого отрезка еще раз: ";
			}

			cin >> y1;

		} while (cin.fail());

		tmp.SetY1(y1);

		cout << "Введите координату X2 " << decorCounter << "-ого отрезка: ";

		do
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "Попробуйте ввести координату X2 " << decorCounter << "-ого отрезка еще раз: ";
			}

			cin >> x2;

		} while (cin.fail());

		tmp.SetX2(x2);

		cout << "Введите координату Y2 " << decorCounter << "-ого отрезка: ";

		do
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "Попробуйте ввести координату Y2 " << decorCounter << "-ого отрезка еще раз: ";
			}

			cin >> y2;

		} while (cin.fail());

		tmp.SetY2(y2);

		this->addSegment(tmp);

		cout << endl;
	}
}

void SetOfSegments::printSetOfSegments() const
{
	for (const auto& i : this->segmentSet)
	{
		i.printSegment();
	}
}

bool SetOfSegments::twoSegmentIntersection(const Segment& a, const Segment& b) const
{
	Segment tmp1(b.GetX1(), b.GetY1(), a.GetX1(), a.GetY1());
	Segment tmp2(b.GetX1(), b.GetY1(), a.GetX2(), a.GetY2());
	Segment tmp3(b.GetX1(), b.GetY1(), b.GetX2(), b.GetY2());

	Segment tmp4(a.GetX1(), a.GetY1(), b.GetX2(), b.GetY2());
	Segment tmp5(a.GetX1(), a.GetY1(), b.GetX1(), b.GetY1());
	Segment tmp6(a.GetX1(), a.GetY1(), a.GetX2(), a.GetY2());

	double d1 = direction(tmp3, tmp1);
	//std::cout << d1 << std::endl;
	double d2 = direction(tmp3, tmp2);
	//std::cout << d2 << std::endl;
	double d3 = direction(tmp6, tmp5);
	//std::cout << d3 << std::endl;
	double d4 = direction(tmp6, tmp4);
	//std::cout << d4 << std::endl;

	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
		((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
	{
		return true;
	}
	else if (d1 == 0 && onSegment(tmp1, tmp2))
	{
		return true;
	}
	else if (d2 == 0 && onSegment(tmp3, tmp2))
	{
		return true;
	}
	else if (d3 == 0 && onSegment(tmp4, tmp5))
	{
		return true;
	}
	else if (d4 == 0 && onSegment(tmp6, tmp5))
	{
		return true;
	}
	else
	{
		return false;
	}

}

void SetOfSegments::clear()
{
	segmentSet.clear();
	counter = 0;
	nativeTime = 0;
	effectiveTime = 0;
}

double SetOfSegments::getNativeTime() const
{
	return nativeTime;
}

double SetOfSegments::getEffectiveTime() const
{
	return effectiveTime;
}

bool operator<(const Segment& a, const Segment& b)
{
	return (a.GetX1() < b.GetX1());
}

bool operator>(const Segment& a, const Segment& b)
{
	return (a.GetX1() > b.GetX1());
}

/*=================================================================================================================*/


// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(std::pair<double, double> p, std::pair<double, double> q, std::pair<double, double> r)
{
	if (q.first <= std::max(p.first, r.first) && q.first >= std::min(p.first, r.first) &&
		q.second <= std::max(p.second, r.second) && q.second >= std::min(p.second, r.second))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(std::pair<double, double> p, std::pair<double, double> q, std::pair<double, double> r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/
	// for details of below formula.
	int val = (q.second - p.second) * (r.first - q.first) -
		(q.first - p.first) * (r.second - q.second);

	if (val == 0) return 0;  // collinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Segment s1, Segment s2)
{
	std::pair<double, double> p1 = s1.segmentBegin, q1 = s1.segmentEnd, p2 = s2.segmentBegin, q2 = s2.segmentEnd;

	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

// Find predecessor of iterator in s.
std::set<Event>::iterator pred(std::set<Event>& s, std::set<Event>::iterator it) {
	return it == s.begin() ? s.end() : --it;
}

// Find successor of iterator in s.
std::set<Event>::iterator succ(std::set<Event>& s, std::set<Event>::iterator it) {
	return ++it;
}

// Returns true if any two lines intersect.
int isIntersect(std::vector<Segment>& arr, int n, double& time)
{
	auto start = std::chrono::system_clock::now();

	std::unordered_map<std::string, int> mp;  // to note the pair for which intersection is checked already
	// Pushing all points to a vector of events
	std::vector<Event> e;
	for (int i = 0; i < n; ++i) {
		bool isLeft = (arr[i].segmentBegin.first < arr[i].segmentEnd.first) ? true : false;
		e.push_back(Event(arr[i].segmentBegin.first, arr[i].segmentBegin.second, isLeft, i));
		e.push_back(Event(arr[i].segmentEnd.first, arr[i].segmentEnd.second, !isLeft, i));
	}

	// Sorting all events according to x coordinate.
	sort(e.begin(), e.end(), [](Event& e1, Event& e2) {return e1.x < e2.x; });

	// For storing active segments.
	std::set<Event> s;
	int ans = 0;
	// Traversing through sorted points
	for (int i = 0; i < 2 * n; i++)
	{
		Event curr = e[i];
		int index = curr.index;

		// If current point is left of its segment
		if (curr.isLeft)
		{
			// Get above and below points
			auto next = s.lower_bound(curr);
			auto prev = pred(s, next);
			// Check if current point intersects with
			// any of its adjacent
			bool flag = false;
			if (next != s.end() && doIntersect(arr[next->index], arr[index])) {
				std::string s = std::to_string(next->index + 1) + " " + std::to_string(index + 1);
				if (mp.count(s) == 0) { mp[s]++; ans++; } //if not already checked we can increase count in map
			}
			if (prev != s.end() && doIntersect(arr[prev->index], arr[index])) {
				std::string s = std::to_string(prev->index + 1) + " " + std::to_string(index + 1);
				if (mp.count(s) == 0) { mp[s]++; ans++; } //if not already checked we can increase count in map
			}
			// if same line segment is there then decrease answer as it got increased twice
			if (prev != s.end() && next != s.end() && next->index == prev->index)ans--;


			// Insert current point (or event)
			s.insert(curr);
		}

		// If current point is right of its segment
		else
		{
			// Find the iterator
			auto it = s.find(Event(arr[index].segmentBegin.first, arr[index].segmentBegin.second, true, index));
			// Find above and below points
			auto next = succ(s, it);
			auto prev = pred(s, it);

			// If above and below point intersect
			if (next != s.end() && prev != s.end())
			{
				std::string s = std::to_string(next->index + 1) + " " + std::to_string(prev->index + 1);
				std::string s1 = std::to_string(prev->index + 1) + " " + std::to_string(next->index + 1);
				if (mp.count(s) == 0 && mp.count(s1) == 0 && doIntersect(arr[prev->index], arr[next->index]))
					ans++;
				mp[s]++;
			}

			// Remove current segment
			s.erase(it);

		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> sec = end - start;

	std::cout << "Время работы \"эффективного\" алгоритма: " << sec.count() << " сек " << std::endl;

	time = sec.count();

	int result = (ans > 0) ? 1 : 0;

	return result;
}
