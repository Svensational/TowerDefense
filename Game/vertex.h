#ifndef VERTEX_H
#define VERTEX_H

// v: x, y, z, w
// c: r, g, b, a
// t: s, t, p, q

struct Vertex_V3F {
   float x, y, z;
};

struct Vertex_T2F_V3F {
   float s, t;
   float x, y, z;
};

#endif // VERTEX_H
