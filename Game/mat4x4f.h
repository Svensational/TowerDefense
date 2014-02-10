#ifndef MAT4X4F_H
#define MAT4X4F_H
#include <array>

class Vec3f;
class Point3f;

class Mat4x4f
{
public:
   Mat4x4f();
   void loadIdentity();
   Mat4x4f operator*(Mat4x4f const & other) const;
   Mat4x4f & operator*=(Mat4x4f const & other);
   Mat4x4f transposed() const;
   Mat4x4f & transpose();
   Mat4x4f inverted() const;
   Mat4x4f & invert();

   static Mat4x4f translation(Vec3f const & trans);
   static Mat4x4f scaling(float x, float y, float z=1.0f);
   static Mat4x4f rotation(float angle, Vec3f axis);
   static Mat4x4f lookAt(Point3f const & eye, Point3f const & center, Vec3f const & up);
   static Mat4x4f ortho(float left, float right, float bottom, float top, float near=-1.0f, float far=1.0f);
   static Mat4x4f frustum(float left, float right, float bottom, float top, float near, float far);
   static Mat4x4f perspective(float fovy, float aspect, float near, float far);

private:
   std::array<float, 16> elements;

   void gaussJordanLine(float * source, float * target, float factor) const;
};

#endif // MAT4X4F_H
