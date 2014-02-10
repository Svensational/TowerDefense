#include "vec3f.h"
#include <cmath>
#include "vec2f.h"

Vec3f::Vec3f(float x, float y, float z) :
   elements{x, y, z}
{
}

Vec3f::Vec3f(Vec2f const & vec, float z) :
   elements{vec.elements[0],
            vec.elements[1],
            z}
{
}

Vec3f::Vec3f(Point3f const & point) :
   elements(point.elements)
{
}

Vec3f::Vec3f(Point3f const & a, Point3f const & b) :
   elements{b.elements[0]-a.elements[0],
            b.elements[1]-a.elements[1],
            b.elements[2]-a.elements[2]}
{
}

float Vec3f::dotProd(Vec3f const & vec) {
   return elements[0]*vec.elements[0] +
          elements[1]*vec.elements[1] +
          elements[2]*vec.elements[2];
}

Vec3f Vec3f::crossProd(Vec3f const & vec) {
   return Vec3f(elements[1]*vec.elements[2]-elements[2]*vec.elements[1],
                elements[2]*vec.elements[0]-elements[0]*vec.elements[2],
                elements[0]*vec.elements[1]-elements[1]*vec.elements[0]);
}

float Vec3f::length() {
   return sqrt(dotProd(*this));
}

Vec3f Vec3f::normalized() {
   return *this / length();
}

Vec3f & Vec3f::normalize() {
   return operator/=(length());
}

Vec3f Vec3f::operator+(Vec3f const & vec) const {
   return Vec3f(*this)+=vec;
}

Vec3f & Vec3f::operator+=(Vec3f const & vec) {
   for (int i=0; i<3; ++i) {
      elements[i]+=vec.elements[i];
   }
   return *this;
}

Vec3f Vec3f::operator-() const {
   return Vec3f(-elements[0],
                -elements[1],
                -elements[2]);
}

Vec3f Vec3f::operator-(Vec3f const & vec) const {
   return Vec3f(*this)-=vec;
}

Vec3f & Vec3f::operator-=(Vec3f const & vec) {
   for (int i=0; i<3; ++i) {
      elements[i]-=vec.elements[i];
   }
   return *this;
}

Vec3f Vec3f::operator*(float a) const {
   return Vec3f(*this)*=a;
}

Vec3f & Vec3f::operator*=(float a) {
   for (int i=0; i<3; ++i) {
      elements[i]*=a;
   }
   return *this;
}

Vec3f Vec3f::operator/(float a) const {
   return Vec3f(*this)/=a;
}

Vec3f & Vec3f::operator/=(float a) {
   for (int i=0; i<3; ++i) {
      elements[i]/=a;
   }
   return *this;
}

float & Vec3f::operator[](int i) {
   return elements[i];
}

float Vec3f::operator[](int i) const {
   return elements[i];
}

Vec3f::operator float const * () const {
   return elements.data();
}



Point3f::Point3f(float x, float y, float z) :
   elements{x, y, z}
{
}

Point3f::Point3f(Vec3f const & vec) :
   elements(vec.elements)
{
}

Point3f Point3f::operator+(Vec3f const & vec) const {
   return Point3f(*this)+=vec;
}

Point3f & Point3f::operator+=(Vec3f const & vec) {
   for (int i=0; i<3; ++i) {
      elements[i]+=vec.elements[i];
   }
   return *this;
}

Vec3f Point3f::operator-(Point3f const & point) const {
   return Vec3f(elements[0]-point.elements[0],
                elements[1]-point.elements[1],
                elements[2]-point.elements[2]);
}

Point3f Point3f::operator-(Vec3f const & vec) const {
   return Point3f(*this)-=vec;
}

Point3f & Point3f::operator-=(Vec3f const & vec) {
   for (int i=0; i<3; ++i) {
      elements[i]-=vec.elements[i];
   }
   return *this;
}

Point3f::operator float const * () const {
   return elements.data();
}
