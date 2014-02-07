#include "size2i.h"

Size2i::Size2i(int width, int height) :
   size{width, height}
{
}

int Size2i::width() const {
   return size[0];
}

int & Size2i::width() {
   return size[0];
}

int Size2i::height() const {
   return size[1];
}

int & Size2i::height() {
   return size[1];
}

float Size2i::aspectRatio() const {
   return size[0]/float(size[1]);
}

int Size2i::area() const {
   return size[0]*size[1];
}
