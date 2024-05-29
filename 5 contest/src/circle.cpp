#include <cmath>
#include "../circle.h"
#include "../point.h"
#include "../vector.h"
#include "../segment.h"
#include "../line.h"

geometry::Circle::Circle(Point center, int radius)
    : center_(&*static_cast<Point *>(center.Clone().release())), radius_(radius) {
}
geometry::Circle &geometry::Circle::Move(const Vector &move_vector) {
  center_->Move(move_vector);
  return *this;
}
geometry::Circle::Circle(const Circle &other) : Circle::Circle(*other.center_, other.radius_) {
}
bool geometry::Circle::ContainsPoint(const Point &point) const {
  return center_->SquaredDistance(point) <= radius_ * radius_;
}
bool geometry::Circle::CrossesSegment(const Segment &segment) const {
  // Extract segment points
  const Point &p1 = *segment.point1_;
  const Point &p2 = *segment.point2_;

  if (center_->SquaredDistance(p1) == radius_ * radius_ || center_->SquaredDistance(p2) == radius_ * radius_) {
    return true;
  }
  if (ContainsPoint(p1) && ContainsPoint(p2)) {
    return false;
  }
  if (ContainsPoint(p1) != ContainsPoint(p2)) {
    return true;
  }
  if ((p1 - *center_).IsColinear(p2 - *center_)) {
    return true;
  }

  // Vector from p1 to p2
  Vector d = p2 - p1;

  // Vector from p1 to the circle's center
  Vector f = *center_ - p1;

  // Project the center of the circle onto the line defined by the segment
  double t = static_cast<double>(f * d) / static_cast<double>(d * d);

  // Clamp t to the range [0, 1] to ensure the projection falls within the segment
  t = std::max(0.0, std::min(1.0, t));

  // Calculate the closest point on the segment to the circle's center
  double closest_x = p1.X() + d.X() * t;
  double closest_y = p1.Y() + d.Y() * t;

  // Check if this distance is within the circle's radius
  return pow(center_->X() - closest_x, 2) + pow(center_->Y() - closest_y, 2) <= static_cast<double>(radius_ * radius_);
}
std::unique_ptr<geometry::IShape> geometry::Circle::Clone() const {
  return std::make_unique<Circle>(*center_, radius_);
}
std::string geometry::Circle::ToString() const {
  return "Circle(" + center_->ToString() + ", " + std::to_string(radius_) + ")";
}
