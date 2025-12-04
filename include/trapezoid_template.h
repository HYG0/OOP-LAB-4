#pragma once
#include "figure_template.h"
#include <cmath>

template <Scalar T> class Trapezoid : public Figure<T> {
public:
  Trapezoid() : Figure<T>(4) {}

  double GetArea() const override {
    double sum = 0;
    for (size_t i = 0; i < 4; ++i) {
      size_t j = (i + 1) % 4;
      sum += this->points[i].x * this->points[j].y -
             this->points[j].x * this->points[i].y;
    }
    return std::fabs(sum) * 0.5;
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
    double side2 = this->Distance(this->points[1], this->points[2]);
    double side3 = this->Distance(this->points[2], this->points[3]);
    double side4 = this->Distance(this->points[3], this->points[0]);

    // Проверяем, что боковые стороны равны (равнобедренная трапеция)
    // Стороны 2 и 4 должны быть равны (боковые стороны)
    return std::fabs(side1 - side3) < epsilon;
  }
};
