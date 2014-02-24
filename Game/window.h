#ifndef WINDOW_H
#define WINDOW_H

#include "glfwwindow.h"
#include "mat4f.h"
#include "vertexarrayobject.h"
#include "vertexbufferobject.h"
#include "indexbufferobject.h"
#include "shaderobject.h"
#include "programobject.h"
#include "texture2d.h"
#include "vertex.h"

class Window : public GLFWWindow {

public:
   Window();
   ~Window();
   void update(double deltaTime);
   void onResized(Size2i newSize);

private:
   Mat4f modelMat;
   Mat4f viewMat;
   Mat4f projectionMat;
   VAO testVAO;
   VBO<Vertex_V3F_T2F> testVBO;
   IBOub testIBO;
   ShaderObject testVertexShader;
   ShaderObject testFragmentShader;
   ProgramObject testProgram;
   Texture2D testTexture;

   void initGL();
};

#endif // WINDOW_H
