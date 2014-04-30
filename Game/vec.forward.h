#ifndef VEC_FORWARD_H
#define VEC_FORWARD_H
#include <cstddef>

template <size_t n, typename T> class Vec;
using Vec2f = Vec<2u, float>;
using Vec3f = Vec<3u, float>;
using Vec4f = Vec<4u, float>;
using Vec2d = Vec<2u, double>;

template <size_t n, typename T> class Point;
//using Point2i = Point<2, int>;
using Point2f = Point<2u, float>;
using Point3f = Point<3u, float>;
using Point2d = Point<2u, double>;

#endif // VEC_FORWARD_H