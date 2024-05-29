#include "../segment.h"
#include "../point.h"
#include "../vector.h"
#include "../ray.h"
#include "../line.h"
#include "../circle.h"

template <typename T>
int geometry::Sign(T val) {
  return (T(0) < val) - (val < T(0));
}

geometry::Segment::Segment(Point point1, Point point2)
    : point1_(&*static_cast<Point *>(point1.Clone().release()))
    , point2_(&*static_cast<Point *>(point2.Clone().release())) {
}
geometry::Segment::Segment(const Segment &other) : Segment::Segment(*other.point1_, *other.point2_) {
}
geometry::Segment &geometry::Segment::Move(const Vector &move_vector) {
  point1_->Move(move_vector);
  point2_->Move(move_vector);
  return *this;
}
bool geometry::Segment::ContainsPoint(const Point &point) const {
  // Colinear check
  if (!(*point2_ - *point1_).IsColinear(point - *point1_)) {
    return false;
  }
  // Check if belongs to the region of the segment
  int min_x = std::min(point1_->X(), point2_->X());
  int max_x = std::max(point1_->X(), point2_->X());
  int min_y = std::min(point1_->Y(), point2_->Y());
  int max_y = std::max(point1_->Y(), point2_->Y());
  return min_x <= point.X() && point.X() <= max_x && min_y <= point.Y() && point.Y() <= max_y;
}
bool geometry::Segment::CrossesSegment(const Segment &segment) const {
  // The sign of the Z component must be different or zero when dividing one segment by another
  int segment1_z1 = (*point2_ - *point1_).ProductZ(*segment.point1_ - *point1_);
  int segment1_z2 = (*point2_ - *point1_).ProductZ(*segment.point2_ - *point1_);
  bool cross_if_colinear = ContainsPoint(*segment.point1_) || ContainsPoint(*segment.point2_) ||
                           segment.ContainsPoint(*point1_) || segment.ContainsPoint(*point2_);
  if (!((segment1_z1 * segment1_z2 == 0 && cross_if_colinear) || Sign(segment1_z1) != Sign(segment1_z2))) {
    return false;
  }
  int segment2_z1 = (*segment.point2_ - *segment.point1_).ProductZ(*point1_ - *segment.point1_);
  int segment2_z2 = (*segment.point2_ - *segment.point1_).ProductZ(*point2_ - *segment.point1_);
  return (segment2_z1 * segment2_z2 == 0 && cross_if_colinear) || Sign(segment2_z1) != Sign(segment2_z2);
}
std::unique_ptr<geometry::IShape> geometry::Segment::Clone() const {
  return std::make_unique<Segment>(*point1_, *point2_);
}
std::string geometry::Segment::ToString() const {
  return "Segment(" + point1_->ToString() + ", " + point2_->ToString() + ")";
}
geometry::Line geometry::Segment::ToLine() const {
  return Line(*point1_, *point2_);
}
