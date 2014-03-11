#include "size2i.h"

Size2i::Size2i(int width, int height) :
   size{width, height}
{
}

int Size2i::area() const {
   return size[0]*size[1];
}

float Size2i::aspectRatio() const {
   return size[0]/float(size[1]);
}

int Size2i::height() const {
   return size[1];
}

int & Size2i::height() {
   return size[1];
}

int Size2i::max() const {
   return std::max(size[0], size[1]);
}

int Size2i::min() const {
   return std::min(size[0], size[1]);
}

int Size2i::width() const {
   return size[0];
}

int & Size2i::width() {
   return size[0];
}



Pos2i::Pos2i(int x, int y) :
   pos{x, y}
{
}

int Pos2i::max() const {
   return std::max(pos[0], pos[1]);
}

int Pos2i::min() const {
   return std::min(pos[0], pos[1]);
}

int Pos2i::x() const {
   return pos[0];
}

int & Pos2i::x() {
   return pos[0];
}

int Pos2i::y() const {
   return pos[1];
}

int & Pos2i::y() {
   return pos[1];
}
