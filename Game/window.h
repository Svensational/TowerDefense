#ifndef WINDOW_H
#define WINDOW_H

#include "glfwwindow.h"
#include "vertexarrayobject.h"
#include "vertexbufferobject.h"
#include "shaderobject.h"
#include "programobject.h"

class Window : public GLFWWindow {

public:
   Window();
   ~Window();
   void update(double deltaTime);
   void onResized(Size2i newSize);

private:
   VAO testVAO;
   VBO testVBO;
   ShaderObject testVertexShader;
   ShaderObject testFragmentShader;
   ProgramObject testProgram;


   void initGL();
};

#endif // WINDOW_H
