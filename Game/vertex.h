#ifndef VERTEX_H
#define VERTEX_H
#include <array>
#include "vec.h"

struct Ver3f_Tex2f {
   Point3f ver;
   Point2f tex;
};

struct Ver3f_Nor3f_Tan3f_Tex2f {
   Point3f ver;
   Vec3f   nor;
   Vec3f   tan;
   Point2f tex;
};

#endif // VERTEX_H
