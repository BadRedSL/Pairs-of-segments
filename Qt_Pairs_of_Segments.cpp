#include <iostream>
#include <vector>
#include <utility>

#include <QApplication>
#include <QtWidgets>
#include <QPainter>
#include <QtMath>

#include "Segment.h"
#include "Class_set_of_segments.h"
#include "Mainw.h"


//основная функция
int main(int argc, char* argv[])
{

	setlocale(LC_ALL, "rus");

	/*==================================================================================================*/
	
	/*SetOfSegments test1;

	std::vector<std::pair<double, double>> points1;
	std::vector<std::pair<double, double>> points12;

	size_t n1 = 1;

	for (size_t i = 0; n1 <= 1001; ++i)
	{

		test1.autoGenerator(n1);
		std::cout << test1.intersection() << std::endl;
		std::cout << test1.effectiveIntersection() << std::endl;

		points1.push_back(std::pair<double, double>(n1, test1.getNativeTime()));
		points12.push_back(std::pair<double, double>(n1, test1.getEffectiveTime()));

		n1 += 100;
		test1.clear();

	}


	QApplication a1(argc, argv); 
	mainw* sw1 = new mainw(points1, points12, "N");
	sw1->show();
	return a1.exec();*/

	/*==================================================================================================*/

	/*SetOfSegments test2;

	std::vector<std::pair<double, double>> points2;
	std::vector<std::pair<double, double>> points22;

	size_t n2 = 1;

	for (size_t i = 0; n2 <= 1001; ++i)
	{

		test2.autoGenerator(n2);
		std::cout << test2.intersection() << std::endl;
		std::cout << test2.effectiveIntersection() << std::endl;

		points2.push_back(std::pair<double, double>(n2, test2.getNativeTime()));
		points22.push_back(std::pair<double, double>(n2, test2.getEffectiveTime()));

		n2 += 1;
		test2.clear();

	}


	QApplication a2(argc, argv);
	mainw* sw2 = new mainw(points2, points22, "N");
	sw2->show();
	return a2.exec();*/

	/*==================================================================================================*/

	/*SetOfSegments test3;

	std::vector<std::pair<double, double>> points3;
	std::vector<std::pair<double, double>> points32;

	std::vector<double> r3;
	double lenght3 = 0.001;
	size_t n3 = 1;

	for (size_t j = 0; n3 < 10001; ++j)
	{

		for (size_t i = 0; i < n3; ++i)
		{
			r3.push_back(lenght3);
		}

		test3.autoRGenerator(n3, r3);
		std::cout << test3.intersection() << std::endl;
		std::cout << test3.effectiveIntersection() << std::endl;

		points3.push_back(std::pair<double, double>(n3, test3.getNativeTime()));
		points32.push_back(std::pair<double, double>(n3, test3.getEffectiveTime()));

		n3 += 100;
		r3.clear();
		test3.clear();
	}
	
	QApplication a3(argc, argv);
	mainw* sw3 = new mainw(points3, points32, "N");
	sw3->show();
	return a3.exec();*/

	/*==================================================================================================*/

	SetOfSegments test4;

	std::vector<std::pair<double, double>> points4;
	std::vector<std::pair<double, double>> points42;

	std::vector<double> r4;
	double lenght4 = 0.0001;
	size_t n4 = 1000;

	for (size_t i = 0; lenght4 < 0.01; ++i)
	{
		for (size_t i = 0; i < n4; ++i)
		{
			r4.push_back(lenght4);
		}

		test4.autoRGenerator(n4, r4);
		std::cout << test4.intersection() << std::endl;
		std::cout << test4.effectiveIntersection() << std::endl;

		points4.push_back(std::pair<double, double>(lenght4, test4.getNativeTime()));
		points42.push_back(std::pair<double, double>(lenght4, test4.getEffectiveTime()));

		lenght4 += 0.0001;
		r4.clear();
		test4.clear();

	}

	QApplication a4(argc, argv);
	mainw* sw4 = new mainw(points4, points42, "R");
	sw4->show();
	return a4.exec();

	return 0;
}