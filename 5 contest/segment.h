#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include <memory>
#include "shape.h"

namespace geometry {
class Point;
class Vector;
class Ray;
class Line;
class Circle;

template <typename T>
int Sign(T val);

class Segment : public IShape {
 private:
  std::unique_ptr<Point> point1_;
  std::unique_ptr<Point> point2_;

 public:
  ~Segment() override = default;
  Segment(Point point1, Point point2);
  Segment(const Segment &other);
  Segment &Move(const Vector &move_vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
  Line ToLine() const;

  friend class Ray;
  friend class Circle;
};
}  // namespace geometry

#endif
