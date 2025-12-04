#include "../include/hexagon.h"
#include <cmath>
// #include <stdexcept>

Hexagon::Hexagon() : Figure{} {
    size = 6;
}

Hexagon::Hexagon(const std::initializer_list<Point>& lst)
    : Figure(lst)
{
    if (lst.size() != 6)
        throw std::invalid_argument("Hexagon must have exactly 6 points");
}

Hexagon::Hexagon(const Point* pts)
    : Figure(pts, 6)
{
}

bool Hexagon::isCorrect() {
    if (size != 6) {
        throw std::invalid_argument("Enter 6 points");
    }

    return Figure::isCorrect();
}

void Hexagon::CountCenter() {
    const Point* p = GetArray();
    double cx = 0, cy = 0;

    for (size_t i = 0; i < 6; ++i) {
        cx += p[i].x;
        cy += p[i].y;
    }

    center = { cx / 6, cy / 6 };
}

void Hexagon::CountArea() {
    const Point* p = GetArray();
    double sum = 0;

    for (int i = 0; i < 6; ++i) {
        int j = (i + 1) % 6;
        sum += p[i].x * p[j].y - p[j].x * p[i].y;
    }

    area = std::fabs(sum) * 0.5;
}
