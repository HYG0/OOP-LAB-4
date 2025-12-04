#pragma once
#include "figure_template.h"
#include <cmath>

template <Scalar T> class Pentagon : public Figure<T> {
public:
  Pentagon() : Figure<T>(5) {}

  double GetArea() const override {
    double sum = 0;
    for (size_t i = 0; i < 5; ++i) {
      size_t j = (i + 1) % 5;
      sum += this->points[i].x * this->points[j].y -
             this->points[j].x * this->points[i].y;
    }
    return std::fabs(sum) * 0.5;
  }

  Point<T> GetCenter() const override {
    T cx = 0, cy = 0;
    for (size_t i = 0; i < 5; ++i) {
      cx += this->points[i].x;
      cy += this->points[i].y;
    }
    return Point<T>(cx / 5, cy / 5);
  }

  bool IsValid() const override {
    const double epsilon = 0.5;
    double side1 = this->Distance(this->points[0], this->points[1]);
    for (size_t i = 1; i < 5; ++i) {
      double side = this->Distance(this->points[i], this->points[(i + 1) % 5]);
      // printf("Result: %f\n", std::fabs(side - side1));
      if (std::fabs(side - side1) > epsilon) {
        return false;
      }
    }
    return true;
  }
};
