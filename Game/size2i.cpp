#include "size2i.h"
#include <algorithm>

Size2i::Size2i() :
   width(0), height(0)
{
}

Size2i::Size2i(int width, int height) :
   width(width), height(height)
{
}

int Size2i::area() const {
   return width*height;
}

float Size2i::aspectRatio() const {
   return width/float(height);
}

int Size2i::max() const {
   return std::max(width, height);
}

int Size2i::min() const {
   return std::min(width, height);
}



Point2i::Point2i() :
   x(0), y(0)
{
}

Point2i::Point2i(int x, int y) :
   x(x), y(y)
{
}

int Point2i::max() const {
   return std::max(x, y);
}

int Point2i::min() const {
   return std::min(x, y);
}



Rect2i::Rect2i() {
}

Rect2i::Rect2i(int left, int bottom, int width, int height) :
   pos(left, bottom), _size(width, height)
{
}

Rect2i::Rect2i(Point2i const & pos, Size2i const & size) :
   pos(pos), _size(size)
{
}

Rect2i::Rect2i(Point2i const & a, Point2i const & b) :
   pos(std::min(a.x, b.x), std::min(a.y, b.y)),
   _size(std::max(a.x, b.x)-pos.x, std::max(a.y, b.y)-pos.y)
{
}

int Rect2i::bottom() const {
   return pos.y;
}

int Rect2i::height() const {
   return _size.height;
}

Size2i const & Rect2i::size() const {
   return _size;
}

int Rect2i::left() const {
   return pos.x;
}

Point2i Rect2i::lowerLeft() const {
   return pos;
}

Point2i Rect2i::lowerRight() const {
   return Point2i(pos.x+_size.width, pos.y);
}

int Rect2i::right() const {
   return pos.x + _size.width;
}

int Rect2i::top() const {
   return pos.y + _size.height;
}

Point2i Rect2i::upperLeft() const {
   return Point2i(pos.x, pos.y+_size.height);
}

Point2i Rect2i::upperRight() const {
   return Point2i(pos.x+_size.width, pos.y+_size.height);
}

int Rect2i::width() const {
   return _size.width;
}
