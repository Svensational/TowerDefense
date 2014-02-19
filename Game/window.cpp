#include "window.h"
#include "gl_core_4_4.h"
#include "vertex.h"
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
   testProgram.use();

   testVBO.createStorage(BufferObject::STATIC_DRAW, 3*sizeof(Vertex_T2F_V3F));
   Vertex_T2F_V3F * it = (Vertex_T2F_V3F *)testVBO.map(BufferObject::WRITE_ONLY);

   // simple triangle
   it->s = 0.0f;
   it->t = 0.0f;
   it->x = -0.5f;
   it->y = -0.5f;
   it->z = -0.5f;
   ++it;

   it->s = 1.0f;
   it->t = 0.0f;
   it->x = 0.5f;
   it->y = -0.5f;
   it->z = -0.5f;
   ++it;

   it->s = 0.5f;
   it->t = 1.0f;
   it->x = 0.0f;
   it->y = 0.5f;
   it->z = -0.5f;
   testVBO.unmap();

   int index = testProgram.getAttributeLocation("vertexTexCoords");
   testVAO.enableVertexAttributeArray(index);
   testVAO.vertexAttributePointer(index, 2, GL_FLOAT, false, sizeof(Vertex_T2F_V3F), 0);

   index = testProgram.getAttributeLocation("position");
   testVAO.enableVertexAttributeArray(index);
   testVAO.vertexAttributePointer(index, 3, GL_FLOAT, false, sizeof(Vertex_T2F_V3F), 2*sizeof(float));

   glUniform1i(testProgram.getUniformLocation("textureSampler"), 0/*texture image unit*/);
}

void Window::onResized(Size2i newSize) {
   glViewport(0, 0, newSize.width(), newSize.height());
}

void Window::update(double deltaTime) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   testVBO.draw(VBO::TRIANGLES, sizeof(Vertex_T2F_V3F));
   swapBuffers();
}
