#include "vec2f.h"
#include <cmath>

Vec2f::Vec2f(float x, float y) :
   elements{x, y}
{
}

Vec2f::Vec2f(Point2f const & point) :
   elements(point.elements)
{
}

Vec2f::Vec2f(Point2f const & a, Point2f const & b) :
   elements{b.elements[0]-a.elements[0],
            b.elements[1]-a.elements[1]}
{
}

float Vec2f::dotProd(Vec2f const & vec) {
   return elements[0]*vec.elements[0] +
          elements[1]*vec.elements[1];
}

float Vec2f::length() {
   return sqrt(dotProd(*this));
}

Vec2f Vec2f::normalized() {
   return *this / length();
}

Vec2f & Vec2f::normalize() {
   return operator/=(length());
}

Vec2f Vec2f::operator+(Vec2f const & vec) const {
   return Vec2f(*this)+=vec;
}

Vec2f & Vec2f::operator+=(Vec2f const & vec) {
   for (int i=0; i<2; ++i) {
      elements[i]+=vec.elements[i];
   }
   return *this;
}

Vec2f Vec2f::operator-(Vec2f const & vec) const {
   return Vec2f(*this)-=vec;
}

Vec2f & Vec2f::operator-=(Vec2f const & vec) {
   for (int i=0; i<2; ++i) {
      elements[i]-=vec.elements[i];
   }
   return *this;
}

Vec2f Vec2f::operator*(float a) const {
   return Vec2f(*this)*=a;
}

Vec2f & Vec2f::operator*=(float a) {
   for (int i=0; i<2; ++i) {
      elements[i]*=a;
   }
   return *this;
}

Vec2f Vec2f::operator/(float a) const {
   return Vec2f(*this)/=a;
}

Vec2f & Vec2f::operator/=(float a) {
   for (int i=0; i<2; ++i) {
      elements[i]/=a;
   }
   return *this;
}

float & Vec2f::operator[](int i) {
   return elements[i];
}

float Vec2f::operator[](int i) const {
   return elements[i];
}

Vec2f::operator float const * () const {
   return elements.data();
}



Point2f::Point2f(float x, float y) :
   elements{x, y}
{
}

Point2f::Point2f(Vec2f const & vec) :
   elements(vec.elements)
{
}

Point2f Point2f::operator+(Vec2f const & vec) const {
   return Point2f(*this)+=vec;
}

Point2f & Point2f::operator+=(Vec2f const & vec) {
   for (int i=0; i<2; ++i) {
      elements[i]+=vec.elements[i];
   }
   return *this;
}

Vec2f Point2f::operator-(Point2f const & point) const {
   return Vec2f(elements[0]-point.elements[0],
                elements[1]-point.elements[1]);
}

Point2f Point2f::operator-(Vec2f const & vec) const {
   return Point2f(*this)-=vec;
}

Point2f & Point2f::operator-=(Vec2f const & vec) {
   for (int i=0; i<2; ++i) {
      elements[i]-=vec.elements[i];
   }
   return *this;
}

Point2f::operator float const * () const {
   return elements.data();
}
