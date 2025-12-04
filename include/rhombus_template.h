#pragma once
#include "figure_template.h"
#include <cmath>

template <Scalar T> class Rhombus : public Figure<T> {
public:
  Rhombus() : Figure<T>(4) {}

  double GetArea() const override {
    T d1 = std::sqrt(std::pow(this->points[2].x - this->points[0].x, 2) +
                     std::pow(this->points[2].y - this->points[0].y, 2));
    T d2 = std::sqrt(std::pow(this->points[3].x - this->points[1].x, 2) +
                     std::pow(this->points[3].y - this->points[1].y, 2));
    return (d1 * d2) / 2.0;
  }

  Point<T> GetCenter() const override {
    T cx = 0, cy = 0;
    for (size_t i = 0; i < 4; ++i) {
      cx += this->points[i].x;
      cy += this->points[i].y;
    }
    return Point<T>(cx / 4, cy / 4);
  }

  bool IsValid() const override {
    const double epsilon = 1e-6;
    double side1 = this->Distance(this->points[0], this->points[1]);
    for (size_t i = 1; i < 4; ++i) {
      double side = this->Distance(this->points[i], this->points[(i + 1) % 4]);
      if (std::fabs(side - side1) > epsilon) {
        return false;
      }
    }
    return true;
  }
};
