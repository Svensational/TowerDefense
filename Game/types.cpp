#include "types.h"
#include <algorithm>
#include <cmath>

Vec2f::Vec2f(float x, float y) :
   _x(x),
   _y(y)
{}

Vec2f::Vec2f(Size2f const & size) :
   _x(size.width()),
   _y(size.height())
{}

Vec2f::Vec2f(Point2f const & a, Point2f const & b) :
   _x(b.x()-a.x()),
   _y(b.y()-a.y())
{}

float Vec2f::angle() const {
   return std::atan2(_x, _y);
}

Vec2f Vec2f::fromAngle(float angle, float length) {
   return Vec2f(std::sin(angle), std::cos(angle)) * length;
}

float Vec2f::x() const {
   return _x;
}

float Vec2f::y() const {
   return _y;
}

float Vec2f::norm() const {
   return sqrt(dotProd(*this, *this));
}

Vec2f Vec2f::operator+(Vec2f const & vec) const {
   return Vec2f(_x+vec.x(), _y+vec.y());
}

Vec2f Vec2f::operator-(Vec2f const & vec) const {
   return Vec2f(_x-vec.x(), _y-vec.y());
}

Vec2f Vec2f::operator*(float a) const {
   return Vec2f(_x*a, _y*a);
}

Vec2f Vec2f::operator/(float a) const {
   return Vec2f(_x/a, _y/a);
}

float dotProd(Vec2f const & vecA, Vec2f const & vecB) {
   return (vecA.x()*vecB.x() + vecA.y()*vecB.y());
}



Point2f::Point2f(float x, float y) :
   _x(x),
   _y(y)
{}

void Point2f::setX(float x) {
   _x = x;
}

void Point2f::setY(float y) {
   _y = y;
}

float Point2f::x() const {
   return _x;
}

float Point2f::y() const {
   return _y;
}

Point2f Point2f::operator+(Vec2f const & vec) const {
   return Point2f(_x+vec.x(), _y+vec.y());
}

Point2f Point2f::operator-(Vec2f const & vec) const {
   return Point2f(_x-vec.x(), _y-vec.y());
}

Point2f & Point2f::operator+=(Vec2f const & vec) {
   _x += vec.x();
   _y += vec.y();
   return *this;
}

Point2f & Point2f::operator-=(Vec2f const & vec) {
   _x -= vec.x();
   _y -= vec.y();
   return *this;
}

Point2f interpolate(Point2f const & a, Point2f const & b, float alpha) {
   return Point2f(alpha*a.x() + (1.0f-alpha)*b.x(),
                  alpha*a.y() + (1.0f-alpha)*b.y());
}



Rectf::Rectf(float left, float right, float bottom, float top) :
   lowerLeft(Point2f(left, bottom)),
   upperRight(Point2f(right, top)),
   _center(interpolate(lowerLeft, upperRight, 0.5f)),
   _size(Size2f(right-left, top-bottom))
{}

Rectf::Rectf(Point2f const & a, Point2f const & b) :
   lowerLeft(Point2f(std::min(a.x(), b.x()), std::min(a.y(), b.y()))),
   upperRight(Point2f(std::max(a.x(), b.x()), std::max(a.y(), b.y()))),
   _center(interpolate(a, b, 0.5f)),
   _size(Size2f(abs(a.x()-b.x()), abs(a.y()-b.y())))
{}

Rectf::Rectf(Point2f const & point, Size2f const & size) :
      lowerLeft(point - Vec2f(size)/2.0f),
      upperRight(point + Vec2f(size)/2.0f),
      _center(point),
      _size(size)
{}

float Rectf::bottom() const {
   return lowerLeft.y();
}

Point2f Rectf::center() const {
   return _center;
}

float Rectf::height() const {
   return _size.height();
}

float Rectf::left() const {
   return lowerLeft.x();
}

float Rectf::right() const {
   return upperRight.x();
}

Size2f Rectf::size() const {
   return _size;
}

float Rectf::top() const {
   return upperRight.y();
}

float Rectf::width() const {
   return _size.width();
}
