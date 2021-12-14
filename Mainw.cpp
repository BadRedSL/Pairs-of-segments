#include <QApplication>
#include <QtWidgets>
#include <QPainter>
#include <QtMath>
#include <string>
#include <iostream>

#include "Mainw.h"

//обработка события перерисования окна
void mainw::paintEvent(QPaintEvent* event)
{
    
    QPainter p(this); //объект для рисования

    int windowWidth = this->width(), windowHeight = this->height();

    double x0 = 40;
    double y0 = windowHeight - 40.0;

    p.setPen(QPen(Qt::blue, Qt::DotLine)); //цвет и тип пера
    p.drawLine(0, y0, windowWidth, y0); p.drawLine(x0, 0, x0, windowHeight); //координатные оси

    QRect rect0(x0 - 20, y0, 20, 20); //прямоугольник для текста 0
    QRect rect1(x0 - 20, 20, 20, 40); //прямоугольник для текста Т
    QRect rect2(windowWidth-400, y0, windowWidth-300, 20); //прямоугольник для текста s
    QRect rect3(windowWidth /2, windowHeight /2, windowWidth / 2+20, windowHeight / 2+20); //прямоугольник для текста 0
    QRect rect4(windowWidth / 2, windowHeight / 2 +30, windowWidth / 2 + 20, windowHeight / 2 + 50); //прямоугольник для текста 0

    p.setPen(QPen(Qt::red, Qt::SolidLine));
    p.setFont(QFont("Arial", -1, -1, false)); 

    p.drawText(rect0, Qt::AlignCenter, "0");
    p.drawText(rect1, Qt::AlignCenter, "T");
    p.drawText(rect2, Qt::AlignCenter, this->s);

    double mean = 0;
    double mean2 = 0;
    for (const auto& i : this->points)
    {
        mean += i.second;
    }
    mean = mean / points.size();

    for (const auto& i : this->points2)
    {
        mean2 += i.second;
    }
    mean2 = mean2 / points.size();

    p.drawText(rect3, Qt::AlignCenter, "native average time: "+QString::number(mean)+" sec");
    p.drawText(rect4, Qt::AlignCenter, "effective average time: " + QString::number(mean2) + " sec");

    p.setPen(QPen(Qt::red, Qt::DotLine));

    double w = (windowWidth - x0) / points[points.size()-1].first;
    double h = 10 * (windowHeight - y0) / points[points.size()-1].second;

    for (size_t i = 0; i< points.size(); ++i)
    {
        p.drawEllipse(x0 + (w * points[i].first), y0 - (points[i].second * h) - 3, 3, 3);

        if (i != 0)
        {
            p.drawLine(x0 + (w * points[i].first), y0 - (points[i].second * h), x0 + (w * points[i - 1].first), y0 - (points[i - 1].second * h));
        }

        p.drawEllipse(x0 + (w * points2[i].first), y0 - (points2[i].second * h) - 3, 3, 3);

        if (i != 0)
        {
            p.drawLine(x0 + (w * points2[i].first), y0 - (points2[i].second * h), x0 + (w * points2[i - 1].first), y0 - (points2[i - 1].second * h));
        }
    }
   
}


mainw::mainw(std::vector<std::pair<double, double>>& points, std::vector<std::pair<double, double>>& points2, char *s)
{
    this->resize(1000, 600);
    this->move(100, 100);
    this->setWindowTitle("Dependency graph");
    QPalette pl; 
    this->setAutoFillBackground(true); 
    this->setPalette(pl); 

    this->points = points;
    this->points2 = points2;
    this->s = s;
}