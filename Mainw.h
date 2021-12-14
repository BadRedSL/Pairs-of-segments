#pragma once

#include <QApplication>
#include <QtWidgets>
#include <QPainter>
#include <QtMath>

//главное окно
class mainw : public QFrame
{
private:

    std::vector<std::pair<double, double>> points;
    std::vector<std::pair<double, double>> points2;
    char* s;

public:
    explicit mainw(std::vector<std::pair<double, double>> &points, std::vector<std::pair<double, double>>& points2, char* s);
    void paintEvent(QPaintEvent* event);
};
