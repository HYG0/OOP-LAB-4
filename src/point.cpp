#include "../include/point.h"
#include <iostream>


Point::Point() = default;

Point::Point(double x, double y) : x(x), y(y) {}

Point::~Point() = default;

Point& Point::operator=(const Point &other) {
    if (this == &other) return *this;

    x = other.x;
    y = other.y;
    return *this;
}

void Point::set_x(double new_x) {x = new_x;}

void Point::set_y(double new_y) {y = new_y;}

double Point::get_x() const {return x;}

double Point::get_y() const {return y;}