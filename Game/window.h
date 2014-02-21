#ifndef WINDOW_H
#define WINDOW_H

#include "glfwwindow.h"
#include "vertexarrayobject.h"
#include "vertexbufferobject.h"
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
   VAO testVAO;
   VBO<Vertex_T2F_V3F> testVBO;
   ShaderObject testVertexShader;
   ShaderObject testFragmentShader;
   ProgramObject testProgram;
   Texture2D testTexture;

   void initGL();
};

#endif // WINDOW_H
