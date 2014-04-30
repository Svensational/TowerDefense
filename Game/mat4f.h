#ifndef MAT4X4F_H
#define MAT4X4F_H
#include <array>
#include "vec.forward.h"

class Mat4f {

public:
   Mat4f();
   void loadIdentity();
   Mat4f operator*(Mat4f const & other) const;
   Mat4f & operator*=(Mat4f const & other);
   operator float const * () const;
   Mat4f transposed() const;
   Mat4f & transpose();
   Mat4f inverted() const;
   Mat4f & invert();

   static Mat4f translation(Vec3f const & trans);
   static Mat4f scaling(float x, float y, float z=1.0f);
   static Mat4f rotation(float angle, Vec3f axis);
   static Mat4f lookAt(Point3f const & eye, Point3f const & center, Vec3f const & up);
   static Mat4f ortho(float left, float right, float bottom, float top, float near=-1.0f, float far=1.0f);
   static Mat4f frustum(float left, float right, float bottom, float top, float near, float far);
   static Mat4f perspective(float fovy, float aspect, float near, float far);

private:
   std::array<float, 16> elements;

   void gaussJordanLine(float * source, float * target, float factor) const;
};

#endif // MAT4X4F_H
