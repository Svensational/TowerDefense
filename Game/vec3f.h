#ifndef VEC3F_H
#define VEC3F_H
#include <array>

class Point3f;

class Vec3f {
   friend class Point3f;

public:
   Vec3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);
   //Vec3f(Vec2f const & vec);
   explicit Vec3f(Point3f const & point);
   Vec3f(Point3f const & a, Point3f const & b);
   Vec3f operator+(Vec3f const & vec) const;
   Vec3f operator-(Vec3f const & vec) const;
   Vec3f & operator+=(Vec3f const & vec);
   Vec3f & operator-=(Vec3f const & vec);
   Vec3f operator*(float a) const;
   Vec3f operator/(float a) const;
   Vec3f & operator*=(float a);
   Vec3f & operator/=(float a);
   float & operator[](int i);
   float operator[](int i) const;
   operator float const * () const;
   float dotProd(Vec3f const & vec);
   Vec3f crossProd(Vec3f const & vec);
   float length();
   Vec3f normalized();
   Vec3f & normalize();

private:
   std::array<float, 3> elements;
};



class Point3f {
   friend class Vec3f;

public:
   Point3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);
   explicit Point3f(Vec3f const & vec);
   Point3f operator+(Vec3f const & vec) const;
   Point3f operator-(Vec3f const & vec) const;
   Vec3f operator-(Point3f const & point) const;
   Point3f & operator+=(Vec3f const & vec);
   Point3f & operator-=(Vec3f const & vec);
   operator float const * () const;

private:
   std::array<float, 3> elements;
};

#endif // VEC3F_H
