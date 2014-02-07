#ifndef VEC2F_H
#define VEC2F_H
#include <array>

class Point2f;

class Vec2f {
   friend class Point2f;

public:
   Vec2f(float x = 0.0f, float y = 0.0f);
   explicit Vec2f(Point2f const & point);
   Vec2f(Point2f const & a, Point2f const & b);
   Vec2f operator+(Vec2f const & vec) const;
   Vec2f operator-(Vec2f const & vec) const;
   Vec2f & operator+=(Vec2f const & vec);
   Vec2f & operator-=(Vec2f const & vec);
   Vec2f operator*(float a) const;
   Vec2f operator/(float a) const;
   Vec2f & operator*=(float a);
   Vec2f & operator/=(float a);
   float & operator[](int i);
   float operator[](int i) const;
   operator float const * () const;
   float dotProd(Vec2f const & vec);
   float length();
   Vec2f normalized();
   Vec2f & normalize();

private:
   std::array<float, 2> elements;
};



class Point2f {
   friend class Vec2f;

public:
   Point2f(float x = 0.0f, float y = 0.0f);
   explicit Point2f(Vec2f const & vec);
   Point2f operator+(Vec2f const & vec) const;
   Point2f operator-(Vec2f const & vec) const;
   Vec2f operator-(Point2f const & point) const;
   Point2f & operator+=(Vec2f const & vec);
   Point2f & operator-=(Vec2f const & vec);
   operator float const * () const;

private:
   std::array<float, 2> elements;
};

#endif // VEC2F_H
