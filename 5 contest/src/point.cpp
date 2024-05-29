#include <cmath>
#include <memory>
#include "../point.h"
#include "../vector.h"
#include "../segment.h"

geometry::Point::Point(int x, int y) : x_(x), y_(y) {
}
geometry::Point::Point() : Point::Point(0, 0) {
}
geometry::Point::Point(const Point &other) : Point::Point(other.x_, other.y_) {
}
int geometry::Point::X() const {
  return x_;
}
int geometry::Point::Y() const {
  return y_;
}
int geometry::Point::SquaredDistance(const Point &point) const {
  return std::pow((x_ - point.x_), 2) + std::pow((y_ - point.y_), 2);
}
geometry::Point &geometry::Point::Move(const Vector &move_vector) {
  x_ += move_vector.X();
  y_ += move_vector.Y();
  return *this;
}
bool geometry::Point::ContainsPoint(const Point &point) const {
  return x_ == point.x_ && y_ == point.y_;
}
bool geometry::Point::CrossesSegment(const Segment &segment) const {
  return segment.ContainsPoint(*this);
}
std::unique_ptr<geometry::IShape> geometry::Point::Clone() const {
  return std::make_unique<Point>(x_, y_);
}
std::string geometry::Point::ToString() const {
  return "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}
geometry::Vector geometry::Point::operator-(const Point &other) const {
  return Vector(other, *this);
}
