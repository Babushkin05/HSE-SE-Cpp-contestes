#ifndef VECTOR_H
#define VECTOR_H

#include <string>
#include <memory>
#include "shape.h"

namespace geometry {
class Point;

class Vector {
 private:
  int x_;
  int y_;

 public:
  ~Vector() = default;
  Vector(int x, int y);
  Vector(const Point &start, const Point &end);
  int X() const;
  int Y() const;
  Vector operator+() const;
  Vector operator*(int num) const;
  Vector operator/(int num) const;
  Vector operator-() const;
  bool operator==(const Vector &other) const;
  Vector operator+(const Vector &other) const;
  Vector operator-(const Vector &other) const;
  Vector &operator+=(const Vector &other);
  Vector &operator-=(const Vector &other);
  int operator*(const Vector &other) const;
  int ProductZ(const Vector &other) const;
  bool IsColinear(Vector other) const;
  std::string ToString() const;
  std::unique_ptr<geometry::Vector> Clone() const;
};
}  // namespace geometry

#endif
