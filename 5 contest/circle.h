#ifndef CIRCLE_H
#define CIRCLE_H

#include <memory>
#include "shape.h"

namespace geometry {
class Point;
class Vector;
class Segment;

class Circle : public IShape {
 private:
  std::unique_ptr<Point> center_;
  int radius_;

 public:
  ~Circle() override = default;
  Circle(Point center, int radius);
  Circle(const Circle &);
  Circle &Move(const Vector &move_vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry

#endif
