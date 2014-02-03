#ifndef TYPES_H
#define TYPES_H

#include <sstream>

inline std::string itoa(int i) {
   std::stringstream out;
   out << i;
   return out.str();
}



template <typename T>
class Size2 {
public:
   Size2(T width = static_cast<T>(0), T height = static_cast<T>(0)) : _width(width), _height(height) {}
   void set(T width, T height) { _width=width; _height=height; }
   T width() const { return _width; }
   T & width() { return _width; }
   T height() const { return _height; }
   T & height() { return _height; }
   float aspectRatio() const { return _width/float(_height); }
   T area() const { return _width*_height; }
   T min() const { return std::min(_width, _height); }
   T max() const { return std::max(_width, _height); }
private:
   T _width;
   T _height;
};

typedef Size2<int> Size2i;
typedef Size2<float> Size2f;



class Point2f;
class Vec2f {
public:
   Vec2f(float x = 0.0f, float y = 0.0f);
   Vec2f(Size2f const & size);
   Vec2f(Point2f const & a, Point2f const & b);
   Vec2f operator+(Vec2f const & vec) const;
   Vec2f operator-(Vec2f const & vec) const;
   Vec2f operator*(float a) const;
   Vec2f operator/(float a) const;
   float x() const;
   float y() const;
   float norm() const;
   float angle() const;
   static Vec2f fromAngle(float angle, float length = 1.0f);
private:
   float _x;
   float _y;
};

float dotProd(Vec2f const & vecA, Vec2f const & vecB);



class Point2f {
public:
   Point2f(float x = 0.0f, float y = 0.0f);
   void setX(float x);
   void setY(float y);
   Point2f operator+(Vec2f const & vec) const;
   Point2f operator-(Vec2f const & vec) const;
   Point2f & operator+=(Vec2f const & vec);
   Point2f & operator-=(Vec2f const & vec);
   float x() const;
   float y() const;
private:
   float _x;
   float _y;
};

Point2f interpolate(Point2f const & a, Point2f const & b, float alpha);



class Rectf {
public:
   Rectf(float left, float right, float bottom, float top);
   Rectf(Point2f const & a, Point2f const & b);
   Rectf(Point2f const & point, Size2f const & size);
   float left() const;
   float right() const;
   float top() const;
   float bottom() const;
   Size2f size() const;
   float width() const;
   float height() const;
   Point2f center() const;
private:
   Point2f lowerLeft;
   Point2f upperRight;
   Point2f _center;
   Size2f _size;
};

#endif //TYPES_H
