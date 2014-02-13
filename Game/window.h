#ifndef WINDOW_H
#define WINDOW_H

#include "glfwwindow.h"
#include "vertexarrayobject.h"
#include "vertexbufferobject.h"

class Window : public GLFWWindow {

public:
   Window();
   ~Window();
   void update(double deltaTime);

private:
   VAO testVAO;
   VBO testVBO;

   void initGL();
};

#endif // WINDOW_H
