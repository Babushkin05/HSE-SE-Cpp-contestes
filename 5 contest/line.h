#ifndef LINE_H
#define LINE_H

#include <tuple>
#include <string>
#include <memory>
#include "shape.h"

namespace geometry {
class Point;
class Vector;
class Segment;

class Line : public IShape {
 private:
  std::unique_ptr<Point> point1_;
  std::unique_ptr<Point> point2_;

 public:
  ~Line() override = default;
  Line(Point point1, Point point2);
  std::tuple<int, int, int> GetABC() const;
  Line &Move(const Vector &move_vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry

#endif
