#ifndef WINDOW_H
#define WINDOW_H

#include "glfwwindow.h"
#include "mat4f.h"

class Overlay;

class Window : public GLFWWindow {

public:
   Window();
   ~Window();
   void onUpdate(double deltaTime);
   void onResized(Size2i const & newSize);

private:
   double frametime;
   Mat4f viewMat;
   Mat4f projectionMat;
   Overlay * overlay;

   void initGL();
};

#endif // WINDOW_H
