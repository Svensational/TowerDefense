#include "window.h"
#include "gl_core_4_4.h"
#include "overlay.h"

#include "sphere.h"
#include "text.h"
#include "textrenderer.h"

Window::Window() :
   GLFWWindow(Size2i(800, 600), std::string("Tower Defense")), frametime(0),
   overlay(new Overlay())
{
   // needs to be done because it can't be called from the baseclass c'tor
   initGL();
   onResized(size);
}

Window::~Window() {
   delete overlay;
}

void Window::initGL() {
   //hideCursor();
   enableVSync();

   glEnable(GL_CULL_FACE);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   viewMat = Mat4f::lookAt(Point3f(0.0f, 0.0f, 4.0f), Point3f(), Vec3f(0.0f, 1.0f, 0.0f));
}

void Window::onResized(Size2i const & newSize) {
   glViewport(0, 0, newSize.width(), newSize.height());
   projectionMat = Mat4f::perspective(45.0, newSize.aspectRatio(), 0.1f, 10.0f);
}

void Window::onUpdate(double deltaTime) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   static Sphere sphere(Point3f(), 1.0f);
   sphere.render(projectionMat*viewMat, viewMat, deltaTime);

   static int pass = 0;
   static TextRenderer textRenderer;
   static Text text(Mat4f::translation(Vec3f(-2.0f, 1.0f, 0.0f)), "text");
   if (pass == 0) textRenderer.addText(&text);
   ++pass;

   text.setString(toU32String(updatetime) + U" ms");
   //text.setString(toU32String(int(framerate+0.5)) + U" FPS");
   textRenderer.render(projectionMat*viewMat);

   overlay->render();
}
