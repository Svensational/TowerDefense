#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <array>
#include <iostream>
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
   explicit Vec(Vec<m, T> vec) {
      for (int i=0; i<std::min(n, m); ++i) {
         elements[i] = vec[i];
      }
   }

   // other type
   template <typename S>
   explicit Vec(Vec<n, S> vec) {
      for (int i=0; i<n; ++i) {
         elements[i] = T(vec[i]);
      }
   }

   // other size and type
   template <size_t m, typename S>
   explicit Vec(Vec<m, S> vec) {
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

   void debugOutput() {
      std::cout << "(";
      for (int i=0; i<n; ++i) {
         std::cout << elements[i];
         if (i<n-1) std::cout << ", ";
      }
      std::cout << ")" << std::endl;
   }

private:
   std::array<T, n> elements;
};

template <size_t n, typename T>
T dot(Vec<n, T> vec1, Vec<n, T> vec2) {
   T prod = T(0);
   for (int i=0; i<n; ++i) {
      prod += vec1[i] * vec2[i];
   }
   return prod;
}

template <typename T>
Vec<3, T> cross(Vec<3, T> vec1, Vec<3, T> vec2) {
   return Vec<3, T>(vec1[1]*vec2[2] - vec1[2]*vec2[1],
                    vec1[2]*vec2[0] - vec1[0]*vec2[2],
                    vec1[0]*vec2[1] - vec1[1]*vec2[0]);
}



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
   explicit Point(Point<m, T> point) {
      for (int i=0; i<std::min(n, m); ++i) {
         elements[i] = point[i];
      }
   }

   // other type
   template <typename S>
   explicit Point(Point<n, S> point) {
      for (int i=0; i<n; ++i) {
         elements[i] = T(point[i]);
      }
   }

   // other size and type
   template <size_t m, typename S>
   explicit Point(Point<m, S> point) {
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

protected:
   std::array<T, n> elements;
};

template <size_t n, typename T>
double distance(Point<n, T> a, Point<n, T> b) {
   return Vec<n, T>(a, b).length();
}

template <size_t n, typename T>
Point<n, T> mix(Point<n, T> x, Point<n, T> y, float a = 0.5f) {
   Point<n, T> point;
   for (int i=0; i<n; ++i) {
      point[i] = x[i]*(1.0f-a) + y[i]*a;
   }
   return point;
}

#endif // VEC_H
