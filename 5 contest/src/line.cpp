#include "../line.h"
#include "../point.h"
#include "../ray.h"
#include "../segment.h"
#include "../vector.h"
#include <numeric>

geometry::Line::Line(Point point1, Point point2)
    : point1_(&*static_cast<Point *>(point1.Clone().release()))
    , point2_(&*static_cast<Point *>(point2.Clone().release())) {
}
std::tuple<int, int, int> geometry::Line::GetABC() const {
  // Solve equation system with Kramer method
  int A = point2_->Y() - point1_->Y();
  int B = point1_->X() - point2_->X();
  int C = -(A * point1_->X() + B * point1_->Y());

  int gcd = std::gcd(A, std::gcd(B, C));
  if (A < 0) {
    gcd = -gcd;
  }
  A /= gcd;
  B /= gcd;
  C /= gcd;
  return {A, B, C};
}
geometry::Line &geometry::Line::Move(const Vector &move_vector) {
  point1_->Move(move_vector);
  point2_->Move(move_vector);
  return *this;
}
bool geometry::Line::ContainsPoint(const Point &point) const {
  return (*point2_ - *point1_).IsColinear(point - *point1_);
}
bool geometry::Line::CrossesSegment(const Segment &segment) const {
  return Ray(*point1_, *point2_ - *point1_).CrossesSegment(segment) ||
         Ray(*point2_, *point1_ - *point2_).CrossesSegment(segment);
}
std::unique_ptr<geometry::IShape> geometry::Line::Clone() const {
  return std::make_unique<Line>(*point1_, *point2_);
}
std::string geometry::Line::ToString() const {
  std::tuple<int, int, int> abc = GetABC();
  return "Line(" + std::to_string(std::get<0>(abc)) + ", " + std::to_string(std::get<1>(abc)) + ", " +
         std::to_string(std::get<2>(abc)) + ")";
}
