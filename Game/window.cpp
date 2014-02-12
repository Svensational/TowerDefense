#include "window.h"
#include "gl_core_4_4.h"

Window::Window() :
   GLFWWindow(Size2i(800, 600), std::string("Tower Defense"))
{
}

Window::~Window() {
}

void Window::initGL() {
   hideCursor();
   enableVSync();
}
