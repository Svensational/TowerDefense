#ifndef VERTEX_H
#define VERTEX_H
#include <array>

struct Vertex_V3F {
   std::array<float, 3> v;
};

struct Vertex_V3F_T2F {
   std::array<float, 3> v;
   std::array<float, 2> t;
};

struct Vertex_V3F_N3F_T2F {
   std::array<float, 3> v;
   std::array<float, 3> n;
   std::array<float, 2> t;
};

#endif // VERTEX_H
