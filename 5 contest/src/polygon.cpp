#include <algorithm>
#include "../polygon.h"
#include "../point.h"
#include "../vector.h"
#include "../segment.h"

geometry::Polygon::Polygon(std::vector<Point> points) : points_(points) {
}
geometry::Polygon& geometry::Polygon::Move(const Vector& move_vector) {
  for (auto& point : points_) {
    point.Move(move_vector);
  }
  return *this;
}
int64_t geometry::Polygon::DoubledSquare() const {
  // Using Gauss formula
  int64_t ans = points_.back().X() * points_[0].Y() - points_.back().Y() * points_[0].X();
  for (size_t i = 0; i < points_.size() - 1; i++) {
    ans += (static_cast<int64_t>(points_[i].X()) * points_[i + 1].Y() -
            static_cast<int64_t>(points_[i].Y()) * points_[i + 1].X());
  }
  return std::abs(ans);
}
bool geometry::Polygon::ContainsPoint(const Point& point) const {
  int intersections = 0;
  size_t n = points_.size();

  bool on_edge = false;
  for (size_t i = 0; i < n; ++i) {
    const Point& p1 = points_[i];
    const Point& p2 = points_[(i + 1) % n];
    on_edge |= Segment(p1, p2).ContainsPoint(point);

    if ((p1.Y() > point.Y()) != (p2.Y() > point.Y()) &&
        point.X() < (p2.X() - p1.X()) * (point.Y() - p1.Y()) / (p2.Y() - p1.Y()) + p1.X()) {
      intersections++;
    }
  }

  return (intersections % 2) != 0 || on_edge;
}
bool geometry::Polygon::CrossesSegment(const Segment& segment) const {
  for (size_t i = 0; i < points_.size() - 1; i++) {
    if (segment.CrossesSegment(Segment(points_[i], points_[i + 1]))) {
      return true;
    }
  }
  return segment.CrossesSegment(Segment(points_.back(), points_[0]));
}
std::unique_ptr<geometry::IShape> geometry::Polygon::Clone() const {
  return std::make_unique<Polygon>(points_);
}
std::string geometry::Polygon::ToString() const {
  std::string str = "Polygon(";
  for (size_t i = 0; i < points_.size() - 1; i++) {
    str += points_[i].ToString() + ", ";
  }
  str += points_.back().ToString() + ")";
  return str;
}
