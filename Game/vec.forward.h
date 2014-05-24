#ifndef VEC_FORWARD_H
#define VEC_FORWARD_H
#include <cstddef>

template <size_t n, typename T> class Vec;
using Vec2f = Vec<2u, float>;
using Vec2d = Vec<2u, double>;
using Vec3f = Vec<3u, float>;
using Vec4f = Vec<4u, float>;

template <size_t n, typename T> class Point;
using Point2i = Point<2u, int>;
using Point2f = Point<2u, float>;
using Point2d = Point<2u, double>;
using Point3f = Point<3u, float>;

template <typename T> class Size2;
using Size2s  = Size2<short>;
using Size2us = Size2<unsigned short>;
using Size2i  = Size2<int>;
using Size2ui = Size2<unsigned int>;
using Size2f  = Size2<float>;

template <typename T> class Rect;
using Recti = Rect<int>;
using Rectf = Rect<float>;

#endif // VEC_FORWARD_H
