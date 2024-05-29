#ifndef POINT_H
#define POINT_H

#include <string>
#include <memory>
#include "shape.h"

namespace geometry {
class Vector;
class Segment;

class Point : public IShape {
 private:
  int x_;
  int y_;

 public:
  ~Point() override = default;
  Point(int x, int y);
  Point();
  Point(const Point &);
  int X() const;
  int Y() const;
  int SquaredDistance(const Point &point) const;
  Point &Move(const Vector &move_vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
  Vector operator-(const Point &other) const;
};
}  // namespace geometry

#endif
