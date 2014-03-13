#include "window.h"
#include "gl_core_4_4.h"
#include <iostream>

Window::Window() :
   GLFWWindow(Size2i(800, 600), std::string("Tower Defense")),
   sphere(Point3f(), 1.0f)
{
   // needs to be done because it can't be called from the baseclass c'tor
   initGL();
   onResized(size);
}

Window::~Window() {
}

void Window::initGL() {
   //hideCursor();
   enableVSync();

   glEnable(GL_CULL_FACE);
   glEnable(GL_DEPTH_TEST);

   viewMat = Mat4f::lookAt(Point3f(0.0f, 0.0f, 4.0f), Point3f(), Vec3f(0.0f, 1.0f, 0.0f));
}

void Window::onResized(Size2i newSize) {
   glViewport(0, 0, newSize.width, newSize.height);
   projectionMat = Mat4f::perspective(45.0, newSize.aspectRatio(), 0.1f, 10.0f);
}

void Window::update(double deltaTime) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   sphere.render(projectionMat*viewMat, viewMat);
   swapBuffers();
}
