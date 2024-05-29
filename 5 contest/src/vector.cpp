#include <string>
#include <memory>
#include "../vector.h"
#include "../point.h"

geometry::Vector::Vector(int x, int y) : x_(x), y_(y) {
}
geometry::Vector::Vector(const Point &start, const Point &end) : x_(end.X() - start.X()), y_(end.Y() - start.Y()) {
}
int geometry::Vector::X() const {
  return x_;
}
int geometry::Vector::Y() const {
  return y_;
}
geometry::Vector geometry::Vector::operator+() const {
  return Vector(x_, y_);
}
geometry::Vector geometry::Vector::operator*(int num) const {
  return Vector(x_ * num, y_ * num);
}
geometry::Vector geometry::Vector::operator/(int num) const {
  return Vector(x_ / num, y_ / num);
}
geometry::Vector geometry::Vector::operator-() const {
  return *this * (-1);
}
bool geometry::Vector::operator==(const Vector &other) const {
  return x_ == other.x_ && y_ == other.y_;
}
geometry::Vector geometry::Vector::operator+(const Vector &other) const {
  return Vector(x_ + other.x_, y_ + other.y_);
}
geometry::Vector geometry::Vector::operator-(const Vector &other) const {
  return Vector(x_ - other.x_, y_ - other.y_);
}
geometry::Vector &geometry::Vector::operator+=(const Vector &other) {
  *this = *this + other;
  return *this;
}
geometry::Vector &geometry::Vector::operator-=(const Vector &other) {
  *this = *this - other;
  return *this;
}
int geometry::Vector::operator*(const Vector &other) const {
  return x_ * other.x_ + y_ * other.y_;
}
int geometry::Vector::ProductZ(const Vector &other) const {
  return x_ * other.y_ - y_ * other.x_;
}
bool geometry::Vector::IsColinear(Vector other) const {
  return this->ProductZ(other) == 0;
}
std::string geometry::Vector::ToString() const {
  return "Vector(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}
std::unique_ptr<geometry::Vector> geometry::Vector::Clone() const {
  return std::make_unique<Vector>(x_, y_);
}
