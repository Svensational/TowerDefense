#include "mat4f.h"
#include <cmath>
#include <utility>
#include "vec.h"

const float pi = 3.141592654f;

Mat4f::Mat4f() :
   elements{1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f}
{
}

Mat4f Mat4f::frustum(float left, float right, float bottom, float top, float near, float far) {
   Mat4f transform;
   transform.elements[ 0] = 2.0f*near/(right-left);
   transform.elements[ 5] = 2.0f*near/(top-bottom);
   transform.elements[ 8] = (right+left)/(right-left);
   transform.elements[ 9] = (top+bottom)/(top-bottom);
   transform.elements[10] = -(far+near)/(far-near);
   transform.elements[11] = -1.0f;
   transform.elements[14] = -2.0f*far*near/(far-near);
   transform.elements[15] = 0.0f;
   return transform;
}

void Mat4f::gaussJordanLine(float * source, float * target, float factor) const {
   for (int i=0; i<16; i+=4) {
      target[i] += source[i]*factor;
   }
}

Mat4f & Mat4f::invert() {
   return *this = inverted();
}

Mat4f Mat4f::inverted() const {
   Mat4f ori(*this);
   Mat4f inv;
   float factor;
   // 'ori' to upper triangular matrix
   for (int i=0; i<3; ++i) {
      for (int j=1; j<=3-i; ++j) {
         factor = -ori.elements[i*5+j]/ori.elements[i*5];
         gaussJordanLine(ori.elements.data()+i, ori.elements.data()+i+j, factor);
         gaussJordanLine(inv.elements.data()+i, inv.elements.data()+i+j, factor);
      }
   }
   // 'ori' to diagonal matrix
   for (int i=3; i>0; --i) {
      for (int j=1; j<=i; ++j) {
         factor = -ori.elements[i*5-j]/ori.elements[i*5];
         gaussJordanLine(ori.elements.data()+i, ori.elements.data()+i-j, factor);
         gaussJordanLine(inv.elements.data()+i, inv.elements.data()+i-j, factor);
      }
   }
   // 'ori' to identity matrix
   for (int i=0; i<4; ++i) {
      factor = ori.elements[i*5];
      for (int j=0; j<4; ++j) {
         inv.elements[i+j*4] /= factor;
      }
   }
   // 'inv' is now inverse to (*this)
   return inv;
}

Mat4f Mat4f::lookAt(Point3f const & eye, Point3f const & center, Vec3f const & up) {
   Mat4f transform;
   Vec3f f = Vec3f(eye, center).normalized();
   Vec3f s = cross(f, up).normalized();
   Vec3f u = cross(s, f);
   transform.elements[ 0] =  s[0];
   transform.elements[ 1] =  u[0];
   transform.elements[ 2] = -f[0];
   transform.elements[ 4] =  s[1];
   transform.elements[ 5] =  u[1];
   transform.elements[ 6] = -f[1];
   transform.elements[ 8] =  s[2];
   transform.elements[ 9] =  u[2];
   transform.elements[10] = -f[2];
   return Mat4f::translation(-Vec3f(eye))*transform;
}

Mat4f Mat4f::operator*(Mat4f const & other) const {
   Mat4f prod;
   int i1, i2;
   for (int i=0; i<16; ++i) {
      i1 = i%4;
      i2 = (i/4)*4;
      prod.elements[i] = 0;
      for (int j=0; j<4; ++j) {
         prod.elements[i] += elements[i1] * other.elements[i2];
         i1 += 4;
         ++i2;
      }
   }
   return prod;
}

Mat4f & Mat4f::operator*=(Mat4f const & other) {
   return *this = *this * other;
}

Mat4f::operator float const * () const {
   return elements.data();
}

Mat4f Mat4f::ortho(float left, float right, float bottom, float top, float near, float far) {
   Mat4f transform;
   transform.elements[ 0] = 2.0f/(right-left);
   transform.elements[ 5] = 2.0f/(top-bottom);
   transform.elements[10] = -2.0f/(far-near);
   transform.elements[12] = -(right+left)/(right-left);
   transform.elements[13] = -(top+bottom)/(top-bottom);
   transform.elements[14] = -(far+near)/(far-near);
   return transform;
}

Mat4f Mat4f::perspective(float fovy, float aspect, float near, float far) {
   Mat4f transform;
   const float f = 1.0f/tan(fovy*pi/360.0f);
   transform.elements[ 0] = f/aspect;
   transform.elements[ 5] = f;
   transform.elements[10] = (far+near)/(near-far);
   transform.elements[11] = -1.0f;
   transform.elements[14] = 2.0f*far*near/(near-far);
   transform.elements[15] = 0.0f;
   return transform;
}

Mat4f Mat4f::rotation(float angle, Vec3f axis) {
   Mat4f transform;
   axis.normalize();
   const float s = sin(angle*pi/180.0);
   const float c = cos(angle*pi/180.0);
   transform.elements[ 0] = axis[0]*axis[0]*(1.0f-c)+c;
   transform.elements[ 1] = axis[0]*axis[1]*(1.0f-c)+axis[2]*s;
   transform.elements[ 2] = axis[0]*axis[2]*(1.0f-c)-axis[1]*s;
   transform.elements[ 4] = axis[0]*axis[1]*(1.0f-c)-axis[2]*s;
   transform.elements[ 5] = axis[1]*axis[1]*(1.0f-c)+c;
   transform.elements[ 6] = axis[1]*axis[2]*(1.0f-c)+axis[0]*s;
   transform.elements[ 8] = axis[0]*axis[2]*(1.0f-c)+axis[1]*s;
   transform.elements[ 9] = axis[1]*axis[2]*(1.0f-c)-axis[0]*s;
   transform.elements[10] = axis[2]*axis[2]*(1.0f-c)+c;
   return transform;
}

Mat4f Mat4f::scaling(float x, float y, float z) {
   Mat4f transform;
   transform.elements[ 0] = x;
   transform.elements[ 5] = y;
   transform.elements[10] = z;
   return transform;
}

Mat4f Mat4f::translation(Vec3f const & trans) {
   Mat4f transform;
   transform.elements[12] = trans[0];
   transform.elements[13] = trans[1];
   transform.elements[14] = trans[2];
   return transform;
}

Mat4f & Mat4f::transpose() {
   std::swap(elements[ 1], elements[ 4]);
   std::swap(elements[ 2], elements[ 8]);
   std::swap(elements[ 3], elements[12]);
   std::swap(elements[ 6], elements[ 9]);
   std::swap(elements[ 7], elements[13]);
   std::swap(elements[11], elements[14]);
   return *this;
}

Mat4f Mat4f::transposed() const {
   return Mat4f(*this).transpose();
}
