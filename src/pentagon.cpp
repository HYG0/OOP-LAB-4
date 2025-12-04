#include "../include/pentagon.h"
#include <iostream>
#include <cmath>

Pentagon::Pentagon() : Figure{} {
    size = 5;
}

Pentagon::Pentagon(const std::initializer_list<Point>& lst)
    : Figure(lst) 
{
    if (lst.size() != 5)
        throw std::invalid_argument("Pentagon must have exactly 5 points");
}

Pentagon::Pentagon(const Point* pts)
    : Figure(pts, 5) 
{
}

bool Pentagon::isCorrect() {
    if (size != 5) {
        throw std::invalid_argument("Enter 5 points");
        return false;
    }

    return Figure::isCorrect();
}

void Pentagon::CountCenter() {
    const Point* p = GetArray();
    double cx = 0, cy = 0;
    for (size_t i = 0; i < 5; ++i) {
        cx += p[i].x;
        cy += p[i].y;
    }
    center = { cx / 5, cy / 5 };
}

void Pentagon::CountArea() {
    const Point* p = GetArray();
    double sum = 0;

    for (int i = 0; i < 5; ++i) {
        int j = (i + 1) % 5;
        sum += p[i].x * p[j].y - p[j].x * p[i].y;
    }

    area = std::fabs(sum) * 0.5;
}
