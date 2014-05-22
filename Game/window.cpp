#include "window.h"
#include "gl_core_4_4.h"

#include "sphere.h"
#include "font.h"
#include "text.h"
#include "textrenderer.h"
#include <iostream>

Window::Window() :
   GLFWWindow(Size2i(800, 600), std::string("Tower Defense"))
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

void Window::onResized(Size2i const & newSize) {
   glViewport(0, 0, newSize.width(), newSize.height());
   projectionMat = Mat4f::perspective(45.0, newSize.aspectRatio(), 0.1f, 10.0f);
}

void Window::update(double deltaTime) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //static Sphere sphere(Point3f(), 1.0f);
   //sphere.render(projectionMat*viewMat, viewMat, deltaTime);

   static int pass = 0;
   static Font font("fonts/text.ttf");
   static TextRenderer textRenderer;
   static Text text(std::u32string(), &font);
   if (pass == 0) textRenderer.addText(&text);
   ++pass;
   textRenderer.render(projectionMat*viewMat);

   swapBuffers();
}
