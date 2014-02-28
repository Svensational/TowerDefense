#ifndef SPHERE_H
#define SPHERE_H

#include "vec3f.h"
#include "mat4f.h"
#include "vertexarrayobject.h"
#include "vertexbufferobject.h"
#include "indexbufferobject.h"
#include "programobject.h"
#include "texture2d.h"
#include "vertex.h"

class Sphere {

public:
   Sphere(Point3f const & pos, float size);
   virtual ~Sphere();
   void render(Mat4f const & vpMat, Mat4f const & vMat);

private:
   Mat4f modelMat;
   VAO vao;
   VBO<Vertex_V3F_N3F_T2F> vbo;
   IBOus ibo;
   ProgramObject program;
   Texture2D texture;

   void createBuffers();
   void loadProgram();
   void loadTexture();
};

#endif // SPHERE_H
