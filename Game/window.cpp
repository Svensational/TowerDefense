#include "window.h"
#include "gl_core_4_4.h"

Window::Window() :
   GLFWWindow(Size2i(800, 600), std::string("Tower Defense"))
{
   // needs to be done because it can't be called from the baseclass c'tor
   initGL();
}

Window::~Window() {
}

void Window::initGL() {
   hideCursor();
   enableVSync();

   /*testVAO.bind();
   testVBO.bind();
   testVBO.createStorage(BufferObject::STATIC_DRAW, 3*3*sizeof(float));
   float * it = (float *)testVBO.map(BufferObject::WRITE_ONLY);

   // simple triangle
   *it++ = -0.5f;
   *it++ = -0.5f;
   *it++ = -0.5f;

   *it++ = 0.5f;
   *it++ = -0.5f;
   *it++ = -0.5f;

   *it++ = 0.0f;
   *it++ = 0.5f;
   *it++ = -0.5f;

   testVAO.vertexAttributePointer(1, sizeof(float)*3, GL_FLOAT, false, 0, 0);
   testVAO.enableVertexAttributeArray(1);

   testVBO.unmap();*/
}

void Window::update(double deltaTime) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //testVBO.draw(VBO::TRIANGLES, sizeof(float)*3);
   swapBuffers();
}
