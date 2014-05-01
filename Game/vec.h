#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <array>
#include "vec.forward.h"

template <size_t n, typename T>
class Vec {

   friend class Point<n, T>;

public:
   template <typename... Args>
   Vec(Args... args) :
      elements{args...}
   {}

   // other size
   template <size_t m>
   explicit Vec(Vec<m, T> const & vec) {
      for (int i=0; i<std::min(n, m); ++i) {
         elements[i] = vec[i];
      }
   }

   // other type
   template <typename S>
   explicit Vec(Vec<n, S> const & vec) {
      for (int i=0; i<n; ++i) {
         elements[i] = T(vec[i]);
      }
   }

   // other size and type
   template <size_t m, typename S>
   explicit Vec(Vec<m, S> const & vec) {
      for (int i=0; i<std::min(n, m); ++i) {
         elements[i] = T(vec[i]);
      }
   }

   explicit Vec(Point<n, T> const & point) :
      elements(point.elements)
   {}

   Vec(Point<n, T> const & a, Point<n, T> const & b) {
      for (int i=0; i<n; ++i) {
         elements[i] = b[i] - a[i];
      }
   }

   Vec(Size2<T> const & size) :
      elements(size.elements)
   {}

   Vec operator+(Vec const & vec) const {
      return Vec(*this)+=vec;
   }

   Vec operator-() const {
      return Vec(*this) * T(-1);
   }

   Vec operator-(Vec const & vec) const {
      return Vec(*this)-=vec;
   }

   Vec & operator+=(Vec const & vec) {
      for (int i=0; i<n; ++i) {
         elements[i] += vec.elements[i];
      }
      return *this;
   }

   Vec & operator-=(Vec const & vec) {
      for (int i=0; i<n; ++i) {
         elements[i] -= vec.elements[i];
      }
      return *this;
   }

   Vec operator*(T a) const {
      return Vec(*this) *= a;
   }

   Vec operator/(T a) const {
      return Vec(*this) /= a;
   }

   Vec & operator*=(T a) {
      for (int i=0; i<n; ++i) {
         elements[i] *= a;
      }
      return *this;
   }

   Vec & operator/=(T a) {
      for (int i=0; i<n; ++i) {
         elements[i] /= a;
      }
      return *this;
   }

   T & operator[](int i) {
      return elements[i];
   }

   T operator[](int i) const {
      return elements[i];
   }

   operator T const * () const {
      return elements.data();
   }

   double length() {
      return sqrt(dot(*this, *this));
   }

   Vec & normalize() {
      return operator/=(length());
   }

   Vec normalized() {
      return operator/(length());
   }

private:
   std::array<T, n> elements;
};

template <size_t n, typename T>
T dot(Vec<n, T> const & vec1, Vec<n, T> const & vec2) {
   T prod = T(0);
   for (int i=0; i<n; ++i) {
      prod += vec1[i] * vec2[i];
   }
   return prod;
}

template <typename T>
Vec<3, T> cross(Vec<3, T> const & vec1, Vec<3, T> const & vec2) {
   return Vec<3, T>(vec1[1]*vec2[2] - vec1[2]*vec2[1],
                    vec1[2]*vec2[0] - vec1[0]*vec2[2],
                    vec1[0]*vec2[1] - vec1[1]*vec2[0]);
}


////////////////////////////////////////////////////////////////////////////////


template <size_t n, typename T>
class Point {

   friend class Vec<n, T>;

public:
   template <typename... Args>
   Point(Args... args) :
      elements{args...}
   {}

   // other size
   template <size_t m>
   explicit Point(Point<m, T> const & point) {
      for (int i=0; i<std::min(n, m); ++i) {
         elements[i] = point[i];
      }
   }

   // other type
   template <typename S>
   explicit Point(Point<n, S> const & point) {
      for (int i=0; i<n; ++i) {
         elements[i] = T(point[i]);
      }
   }

   // other size and type
   template <size_t m, typename S>
   explicit Point(Point<m, S> const & point) {
      for (int i=0; i<std::min(n, m); ++i) {
         elements[i] = T(point[i]);
      }
   }

   explicit Point(Vec<n, T> const & vec) :
      elements(vec.elements)
   {}

   Point operator+(Vec<n, T> const & vec) const {
      return Point(*this) += vec;
   }

   Point operator-(Vec<n, T> const & vec) const {
      return Point(*this) -= vec;
   }

   Point & operator+=(Vec<n, T> const & vec) {
      for (int i=0; i<n; ++i) {
         elements[i] += vec.elements[i];
      }
      return *this;
   }

   Point & operator-=(Vec<n, T> const & vec) {
      for (int i=0; i<n; ++i) {
         elements[i] -= vec.elements[i];
      }
      return *this;
   }

   T & operator[](int i) {
      return elements[i];
   }

   T operator[](int i) const {
      return elements[i];
   }

   operator T const * () const {
      return elements.data();
   }

private:
   std::array<T, n> elements;
};

template <size_t n, typename T>
double distance(Point<n, T> const & a, Point<n, T> const & b) {
   return Vec<n, T>(a, b).length();
}

template <size_t n, typename T>
Point<n, T> mix(Point<n, T> const & x, Point<n, T> const & y, double a = 0.5) {
   Point<n, T> point;
   for (int i=0; i<n; ++i) {
      point[i] = x[i]*(1.0-a) + y[i]*a;
   }
   return point;
}


////////////////////////////////////////////////////////////////////////////////


template <typename T>
class Size2 {
public:
   Size2(T width, T height) :
      elements{width, height}
   {}

   template <typename S>
   explicit Size2(Size2<S> const & size) :
      elements{T(size.width()), T(size.height())}
   {}

   explicit Size2(Vec<2u, T> const & vec) :
      elements{vec[0], vec[1]}
   {}

   T width() const {
      return elements[0];
   }

   T & width() {
      return elements[0];
   }

   T height() const {
      return elements[1];
   }

   T & height() {
      return elements[1];
   }

   double aspectRatio() const {
      return elements[0]/double(elements[1]);
   }

   T area() const {
      return elements[0]*elements[1];
   }

   T min() const {
      return std::min(elements[0], elements[1]);
   }

   T max() const {
      return std::max(elements[0], elements[1]);
   }

private:
   std::array<T, 2> elements;
};


////////////////////////////////////////////////////////////////////////////////


template <typename T>
class Rect {
public:
   Rect(T left, T bottom, T width, T height) :
      _pos(left, right), _size(width, height)
   {}

   Rect(Point<2u, T> const & pos, Size2<T> const & size) :
      _pos(pos), _size(size)
   {}

   Rect(Point<2u, T> const & a, Point<2u, T> const & b) :
      _pos(std::min(a[0], b[0]), std::min(a[1], b[1])),
      _size(std::max(a[0], b[0])-_pos[0], std::max(a[1], b[1])-_pos[1])
   {}

   T width() const {
      return _size.width();
   }

   T height() const {
      return _size.height();
   }

   Size2<T> const & size() const {
      return _size;
   }

   T left() const {
      return _pos[0];
   }

   T right() const {
      return _pos[0] + _size.width();
   }

   T bottom() const {
      return _pos[1];
   }

   T top() const {
      return _pos[1] + _size.height();
   }

   Point<2u, T> lowerLeft() const {
      return _pos;
   }

   Point<2u, T> lowerRight() const {
      return Point<2u, T>(_pos[0] + _size.width(),
                          _pos[1]);
   }

   Point<2u, T> upperLeft() const {
      return Point<2u, T>(_pos[0],
                          _pos[1] + _size.height());
   }

   Point<2u, T> upperRight() const {
      return Point<2u, T>(_pos[0] + _size.width(),
                          _pos[1] + _size.height());
   }

   Point<2u, T> center() const {
      return Point<2u, T>(_pos[0] + _size.width()/2.0,
                          _pos[1] + _size.height()/2.0);
   }

private:
   Point<2u, T> _pos;
   Size2<T> _size;
};


#endif // VEC_H
