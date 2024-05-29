#include "../ray.h"
#include "../point.h"
#include "../vector.h"
#include "../segment.h"

template <typename T>
int geometry::Sign(T val) {
  return (T(0) < val) - (val < T(0));
}

geometry::Ray::Ray(Point point, Vector vector)
    : point_(&*static_cast<Point *>(point.Clone().release())), vector_(&*vector.Clone().release()) {
}
geometry::Ray::Ray(Point point1, Point point2) : Ray::Ray(point1, point2 - point1) {
}
geometry::Ray &geometry::Ray::Move(const Vector &move_vector) {
  point_->Move(move_vector);
  return *this;
}
bool geometry::Ray::ContainsPoint(const Point &point) const {
  if (*vector_ == Vector(0, 0)) {
    return point_->ContainsPoint(point);
  }
  Vector vector2 = point - *point_;
  return vector_->IsColinear(vector2) && *vector_ * vector2 >= 0;
}
bool geometry::Ray::CrossesSegment(const Segment &segment) const {
  if (*vector_ == Vector(0, 0)) {
    return point_->CrossesSegment(segment);
  }
  int z1 = vector_->ProductZ(*segment.point1_ - *point_);
  int z2 = vector_->ProductZ(*segment.point2_ - *point_);
  if (z1 * z2 == 0) {
    return ContainsPoint(*segment.point1_) || ContainsPoint(*segment.point2_);
  }
  return Sign(z1) != Sign(z2);
}
std::unique_ptr<geometry::IShape> geometry::Ray::Clone() const {
  return std::make_unique<Ray>(*point_, *vector_);
}
std::string geometry::Ray::ToString() const {
  return "Ray(" + point_->ToString() + ", " + vector_->ToString() + ")";
}
