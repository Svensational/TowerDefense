#ifndef WINDOW_H
#define WINDOW_H

#include "glfwwindow.h"
#include "mat4f.h"
#include "sphere.h"

class Window : public GLFWWindow {

public:
   Window();
   ~Window();
   void update(double deltaTime);
   void onResized(Size2i const & newSize);

private:
   Mat4f viewMat;
   Mat4f projectionMat;
   Sphere sphere;

   void initGL();
};

#endif // WINDOW_H
