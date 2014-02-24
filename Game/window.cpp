#include "window.h"
#include "gl_core_4_4.h"
#include "vertex.h"
#include "vec3f.h"
#include <iostream>

Window::Window() :
   GLFWWindow(Size2i(800, 600), std::string("Tower Defense")),
   testVertexShader(ShaderObject::VERTEX_SHADER),
   testFragmentShader(ShaderObject::FRAGMENT_SHADER)
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

   Image testImage;
   testImage.loadPNG("images/test.png");
   testTexture.bind();
   testTexture.createStorage(testImage.getSize());
   testTexture.setImage(testImage);
   testTexture.generateMipmaps();
   testTexture.setMinFilter(Texture::LINEAR);
   testTexture.setMagFilter(Texture::LINEAR);
   testTexture.setMaxAnisotropy();


   testVertexShader.loadSource("shaders/default.vertex.glsl");
   testVertexShader.compile();

   testFragmentShader.loadSource("shaders/default.fragment.glsl");
   testFragmentShader.compile();

   testProgram.attachShader(testVertexShader);
   testProgram.attachShader(testFragmentShader);
   testProgram.link();

   std::cout << "VertexShader: " << testVertexShader.getLog() << std::endl;
   std::cout << "FragmentShader: " << testFragmentShader.getLog() << std::endl;
   std::cout << "Program: " << testProgram.getLog() << std::endl;

   testVAO.bind();
   testVBO.bind();
   testIBO.bind();
   testProgram.use();

   testVBO.createStorage(BufferObject::STATIC_DRAW, 4);
   Vertex_V3F_T2F * it = testVBO.map(BufferObject::WRITE_ONLY);
   it->v = {-0.5f, -0.5f, 0.0f};
   it->t = {0.0f, 0.0f};
   ++it;

   it->v = {0.5f, -0.5f, 0.0f};
   it->t = {1.0f, 0.0f};
   ++it;

   it->v = {0.5f, 0.5f, 0.0f};
   it->t = {1.0f, 1.0f};
   ++it;

   it->v = {-0.5f, 0.5f, 0.0f};
   it->t = {0.0f, 1.0f};
   testVBO.unmap();

   testIBO.createStorage(BufferObject::STATIC_DRAW, 6);
   unsigned char * it2 = testIBO.map(BufferObject::WRITE_ONLY);
   *it2++ = 0;
   *it2++ = 1;
   *it2++ = 2;
   *it2++ = 0;
   *it2++ = 2;
   *it2++ = 3;
   testIBO.unmap();

   testVAO.enableVertexAttributeArray(0);
   testVAO.vertexAttributePointer(0, 3, GL_FLOAT, false, sizeof(Vertex_V3F_T2F), 0);

   testVAO.enableVertexAttributeArray(3);
   testVAO.vertexAttributePointer(3, 2, GL_FLOAT, false, sizeof(Vertex_V3F_T2F), 3*sizeof(float));

   testProgram.setUniform("textureSampler", 0/*texture image unit*/);
   viewMat = Mat4f::lookAt(Point3f(0.0f, 0.0f, 2.0f), Point3f(), Vec3f(0.0f, 1.0f, 0.0f));
}

void Window::onResized(Size2i newSize) {
   glViewport(0, 0, newSize.width(), newSize.height());
   projectionMat = Mat4f::perspective(45.0, newSize.aspectRatio(), 0.1f, 10.0f);
}

void Window::update(double deltaTime) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   testProgram.setUniform("mvp", projectionMat*viewMat*modelMat);
   testIBO.draw(BufferObject::TRIANGLES);
   swapBuffers();
}
