#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <memory>
#include "shape.h"

namespace geometry {
class Point;
class Vector;
class Segment;

class Polygon : public IShape {
 private:
  std::vector<Point> points_;

 public:
  ~Polygon() override = default;
  explicit Polygon(std::vector<Point> points);
  Polygon &Move(const Vector &move_vector) override;
  int64_t DoubledSquare() const;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry

#endif
