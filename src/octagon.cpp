#include "../include/octagon.h"
#include <cmath>
#include <stdexcept>

Octagon::Octagon() : Figure{} {
    size = 6;
}

Octagon::Octagon(const std::initializer_list<Point>& lst)
    : Figure(lst)
{
    if (lst.size() != 8)
        throw std::invalid_argument("Octagon must have exactly 8 points");
}

Octagon::Octagon(const Point* pts)
    : Figure(pts, 8)
{
}

bool Octagon::isCorrect() {
    if (size != 8) {
        throw std::invalid_argument("Enter 8 points");
        return false;
    }

    return Figure::isCorrect();
}

void Octagon::CountCenter() {
    const Point* p = GetArray();
    double cx = 0, cy = 0;

    for (size_t i = 0; i < 8; ++i) {
        cx += p[i].x;
        cy += p[i].y;
    }

    center = { cx / 8, cy / 8 };
}

void Octagon::CountArea() {
    const Point* p = GetArray();
    double sum = 0;

    for (int i = 0; i < 8; ++i) {
        int j = (i + 1) % 8;
        sum += p[i].x * p[j].y - p[j].x * p[i].y;
    }

    area = std::fabs(sum) * 0.5;
}
