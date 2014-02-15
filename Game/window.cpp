#include "window.h"
#include "gl_core_4_4.h"
#include <iostream>

Window::Window() :
   GLFWWindow(Size2i(800, 600), std::string("Tower Defense")),
   testVertexShader(ShaderObject::VERTEX_SHADER),
   testFragmentShader(ShaderObject::FRAGMENT_SHADER)
{
   // needs to be done because it can't be called from the baseclass c'tor
   initGL();
}

Window::~Window() {
}

void Window::initGL() {
   hideCursor();
   enableVSync();

   testVertexShader.loadSource("shaders/default.vertex.glsl");
   testVertexShader.compile();

   testFragmentShader.loadSource("shaders/default.fragment.glsl");
   testFragmentShader.compile();

   testProgram.attachShader(testVertexShader);
   testProgram.attachShader(testFragmentShader);
   testProgram.link();

   //std::cout << "VertexShader: " << testVertexShader.getLog() << std::endl;
   //std::cout << "FragmentShader: " << testFragmentShader.getLog() << std::endl;
   //std::cout << "Program: " << testProgram.getLog() << std::endl;

   testVAO.bind();
   testVBO.bind();
   testProgram.use();

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
   testVBO.unmap();

   int index = testProgram.getAttributeLocation("position");
   testVAO.enableVertexAttributeArray(index);
   testVAO.vertexAttributePointer(index, 3, GL_FLOAT, false, 0, 0);

}

void Window::onResized(Size2i newSize) {
   glViewport(0, 0, newSize.width(), newSize.height());
}

void Window::update(double deltaTime) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   testVBO.draw(VBO::TRIANGLES, sizeof(float)*3);
   swapBuffers();
}
