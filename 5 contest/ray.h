#ifndef RAY_H
#define RAY_H

#include <memory>
#include "shape.h"

namespace geometry {
class Point;
class Vector;
class Segment;

template <typename T>
int Sign(T val);

class Ray : public IShape {
 private:
  std::unique_ptr<Point> point_;
  std::unique_ptr<Vector> vector_;

 public:
  ~Ray() override = default;
  Ray(Point point, Vector vector);
  Ray(Point point1, Point point2);
  Ray &Move(const Vector &move_vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry

#endif
