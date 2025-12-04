#pragma once
#include "point_template.h"
#include <cmath>
#include <iostream>
#include <memory>

template <Scalar T> class Figure {
protected:
  size_t size;
  std::unique_ptr<Point<T>[]> points;

public:
  Figure() : size(0), points(nullptr) {}

  Figure(size_t n) : size(n), points(std::make_unique<Point<T>[]>(n)) {}

  virtual ~Figure() = default;

  Figure(const Figure &other)
      : size(other.size), points(std::make_unique<Point<T>[]>(other.size)) {
    for (size_t i = 0; i < size; ++i) {
      points[i] = other.points[i];
    }
  }

  Figure(Figure &&other) noexcept
      : size(other.size), points(std::move(other.points)) {
    other.size = 0;
  }

  Figure &operator=(const Figure &other) {
    if (this != &other) {
      size = other.size;
      points = std::make_unique<Point<T>[]>(other.size);
      for (size_t i = 0; i < size; ++i) {
        points[i] = other.points[i];
      }
    }
    return *this;
  }

  Figure &operator=(Figure &&other) noexcept {
    if (this != &other) {
      size = other.size;
      points = std::move(other.points);
      other.size = 0;
    }
    return *this;
  }

  bool operator==(const Figure &other) const {
    if (size != other.size)
      return false;
    for (size_t i = 0; i < size; ++i) {
      if (!(points[i] == other.points[i]))
        return false;
    }
    return true;
  }

  virtual explicit operator double() const { return GetArea(); }

  virtual double GetArea() const = 0;
  virtual Point<T> GetCenter() const = 0;
  virtual bool IsValid() const = 0;

  double Distance(const Point<T> &p1, const Point<T> &p2) const {
    double dx = static_cast<double>(p2.x - p1.x);
    double dy = static_cast<double>(p2.y - p1.y);
    return std::sqrt(dx * dx + dy * dy);
  }

  void PrintPoints() const {
    for (size_t i = 0; i < size; ++i) {
      std::cout << "(" << points[i].x << ", " << points[i].y << ") ";
    }
    std::cout << std::endl;
  }

  size_t GetSize() const { return size; }
  const Point<T> &GetPoint(size_t i) const { return points[i]; }

  bool IsCorrect() const {
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = i + 1; j < size; ++j) {
        const double epsilon = 1e-9;
        if (std::fabs(static_cast<double>(points[i].x) -
                      static_cast<double>(points[j].x)) < epsilon &&
            std::fabs(static_cast<double>(points[i].y) -
                      static_cast<double>(points[j].y)) < epsilon) {
          return false;
        }
      }
    }
    return true;
  }

  friend std::ostream &operator<<(std::ostream &out, const Figure<T> &fig) {
    out << "Points: ";
    for (size_t i = 0; i < fig.size; ++i) {
      out << "(" << fig.points[i].x << ", " << fig.points[i].y << ") ";
    }
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Figure<T> &fig) {
    for (size_t i = 0; i < fig.size; ++i) {
      in >> fig.points[i].x >> fig.points[i].y;
      if (in.fail()) {
        throw std::invalid_argument("Enter correct points");
      }
    }
    if (!fig.IsCorrect()) {
      throw std::invalid_argument("Points don't fit. Figure isn't correct.");
    }
    if (!fig.IsValid()) {
      throw std::invalid_argument("Figure is not valid (must be isosceles).");
    }
    return in;
  }
};
