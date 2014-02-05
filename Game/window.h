#ifndef WINDOW_H
#define WINDOW_H

#include "glfwwindow.h"

class Window : public GLFWWindow {

public:
   Window();
   ~Window();

private:
   void initGL();
};

#endif // WINDOW_H
