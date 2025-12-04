#include "../include/figure.h"
#include <cstring>
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <istream>
#include <iterator>
#include <cmath>
#include <math.h>
#include <stdexcept>


Figure::Figure() : size(0), arr_points(nullptr), area(0), center({0, 0}) {};

Figure::Figure(const Point* arr_pointres, size_t sz) : size(sz),
                                                       arr_points(new Point[size]) {
    for (size_t i = 0; i < size; ++i) {
        arr_points[i] = arr_pointres[i];
    }
}

Figure::Figure(const std::initializer_list<Point>& lst) : size(lst.size()),
                                                   arr_points(new Point[size]) {
    std::copy(lst.begin(), lst.end(), arr_points);
}

Figure::Figure(const Figure& other) : size(other.size), arr_points(new Point[size]),
                                    area(other.area), center(other.center) {
    for (size_t i = 0; i < size; ++i) {
        arr_points[i] = other.arr_points[i];
    }
}


Figure& Figure::operator=(const Figure& other) {
    if (this == &other) return *this;

    if (arr_points) {
        delete[] arr_points;
    }

    size = other.size;
    arr_points = new Point[size];
    area = other.area;
    center = other.center;

    for (size_t i = 0; i < size; ++i) {
        arr_points[i] = other.arr_points[i];
    }

    return *this;
}

bool Figure::operator==(const Figure& other) const {
    const double EPS = 1e-6;
    if (size != other.size)
        return false;

    for (size_t i = 0; i < size; ++i) {
        if (std::fabs(arr_points[i].get_x() - other.arr_points[i].get_x()) > EPS ||
            std::fabs(arr_points[i].get_y() - other.arr_points[i].get_y()) > EPS)
            return false;
    }
    return true;
}

Figure::Figure(Figure&& other) noexcept : size(other.size), arr_points(other.arr_points),
                                    area(other.area), center(other.center) {
    other.size = 0;
    other.arr_points = nullptr;
    other.area = 0;
    other.center = {0, 0};
}

Figure::operator double() {
    CountArea();
    return area;
}

void Figure::CountArea() {
    int length_side = sqrt(pow(arr_points[1].x - arr_points[0].x, 2) +
                            pow(arr_points[1].y - arr_points[0].y, 2));
    area = (size * length_side * length_side) / (4 * tan(3.14 / size));
}

void Figure::CountCenter() {
    for (size_t i = 0; i < size; ++i) {
        center.x += arr_points[i].x;
        center.y += arr_points[i].y;
    }

    center.x /= size;
    center.y /= size;
}

Point Figure::GetCenter() {
    CountCenter();
    return center;
}

bool Figure::isCorrect() {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            const double epsilon = 1e-9;
            if (std::fabs(arr_points[i].x - arr_points[j].x) < epsilon &&
                std::fabs(arr_points[i].y - arr_points[j].y) < epsilon) {
                return false;
            }
        }
    }
    
    return true;
}


std::ostream& operator<<(std::ostream& out, const Figure& figure) {
    out << "Точки фигуры:\n";
    for (size_t i = 0; i < figure.size; ++i) {
        out << "(" << figure.arr_points[i].get_x() << ", " << figure.arr_points[i].get_y() << ")" << "\n";
    }

    return out;
}

std::istream& operator>>(std::istream& in, Figure& figure) {
    std::cout << "Вводите точки фигуры в таком формате: x y\n";
    for (size_t i = 0; i < figure.size; ++i) {
        in >> figure.arr_points[i].x >> figure.arr_points[i].y;
        if (in.fail()) {
            throw std::invalid_argument("Enter correct points");
            in.setstate(std::ios::failbit);
        }
    }

    if (!figure.isCorrect()) {
        throw std::invalid_argument("Points don't fit. Figure isn't correct.");
    }
    
    return in;
}

void Figure::PrintPoints() {
    for (size_t i = 0; i < size; ++i) {
        std::cout << i + 1 << ") " << arr_points[i].get_x() << ", " << arr_points[i].get_y() << "\n";
    }
}

double Figure::GetArea() {
    Figure::CountArea();
    return area;
}

const Point* Figure::GetArray() const {
    return arr_points;
}

Figure::~Figure() {
    if (arr_points) {
        delete[] arr_points;
        arr_points = nullptr;
    }
}