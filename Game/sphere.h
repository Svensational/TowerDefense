#ifndef SPHERE_H
#define SPHERE_H

#include "vec.h"
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
   void render(Mat4f const & vpMat, Mat4f const & vMat, double deltaTime = 0.0);
   void renderAndSave(Mat4f const & vpMat, Mat4f const & vMat);

private:
   float angle;
   Mat4f modelMat;
   VAO vao;
   VBO<Pos3f_Nor3f_Tan3f_Tex2f> vbo;
   IBOus ibo;
   ProgramObject program;
   Texture2D texture;
   Texture2D normalMap;

   void createBuffers();
   void loadProgram();
   void loadTexture();
};

#endif // SPHERE_H
