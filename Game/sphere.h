#ifndef SPHERE_H
#define SPHERE_H

#include "vec.h"
#include "mat4f.h"
#include "vertexarrayobject.h"
#include "vertexbufferobject.h"
#include "indexbufferobject.h"
#include "vertex.h"

class Texture2D;
class ProgramObject;

class Sphere {

public:
   Sphere(Point3f const & pos, float size);
   virtual ~Sphere();
   void render(Mat4f const & vpMat, Mat4f const & vMat, double deltaTime = 0.0);
   void renderAndSave(Mat4f const & vpMat, Mat4f const & vMat);

private:
   double angle;
   Mat4f modelMat;
   VAO vao;
   VBO<Pos3f_Nor3f_Tan3f_Tex2f> vbo;
   IBOus ibo;
   ProgramObject * program;
   Texture2D * texture;
   Texture2D * normalMap;

   void createBuffers();
};

#endif // SPHERE_H
