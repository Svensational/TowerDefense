#ifndef VERTEX_H
#define VERTEX_H
#include <array>
#include "vec.h"

struct Pos2f_Tex2f {
   Point2f pos;
   Point2f tex;
};

struct Pos3f_Nor3f_Tan3f_Tex2f {
   Point3f pos;
   Vec3f   nor;
   Vec3f   tan;
   Point2f tex;
};

#endif // VERTEX_H
