#include "sphere.h"
#include <cmath>
#include "gl_core_4_4.h"
#include "renderbufferobject.h"
#include "framebufferobject.h"
#include "shaderobject.h"
#include "programobject.h"
#include "texture2d.h"
#include "resourcemanager.h"

//#include <iostream>

Sphere::Sphere(Point3f const & pos, float size) :
   angle(0.0f),
   modelMat(Mat4f::translation(Vec3f(pos)) * Mat4f::scaling(size, size, size)),
   program(ResourceManager::getGlobalInstance()->getProgram("normalmapped")),
   texture(ResourceManager::getGlobalInstance()->getTexture("test")),
   normalMap(ResourceManager::getGlobalInstance()->getTexture("test_n"))
{
   if (program) {
      program->use();
      program->setUniform("lightDir", Vec3f(1.0f, -1.0f, -1.0f));
      program->setUniform("lightColor", Vec3f(1.0f, 1.0f, 1.0f));
      program->setUniform("textureSampler", 0);
      program->setUniform("normalMapSampler", 1);
   }
   createBuffers();
}

Sphere::~Sphere()
{
}

void Sphere::createBuffers() {
   const int n = 16;
   const double pi = 3.141592654;
   double theta;
   double phi;

   vao.bind();
   vbo.bind();

   vbo.createStorage(BufferObject::STATIC_DRAW, (n+1)*2*n);
   auto * iv = vbo.map(BufferObject::WRITE_ONLY);
   for (int i=0; i<=n; ++i) {
      theta = (i*pi)/double(n);
      for (int j=0; j<2*n; ++j) {
         phi = (j*pi)/double(n);
         iv->pos = {float(sin(theta)*cos(phi)), float(sin(theta)*sin(phi)), float(cos(theta))};
         iv->nor = Vec3f(iv->pos);
         iv->tan = {float(sin(theta+pi/2.0)*cos(phi)), float(sin(theta+pi/2.0)*sin(phi)), float(cos(theta+pi/2.0))};
         iv->tex = {std::abs(j/float(n)-1.0f), i/float(n)};
         ++iv;
      }
   }
   vbo.unmap();

   ibo.bind();
   ibo.createStorage(BufferObject::STATIC_DRAW, 2*n*(2*n+2));
   unsigned short * ii = ibo.map(BufferObject::WRITE_ONLY);
   for (int i=0; i<n; ++i) {
      for (int j=0; j<=2*n; ++j) {
         *ii++ = i*2*n+j%(2*n);
         *ii++ = (i+1)*2*n+j%(2*n);
      }
      *ii++ = 65535;
   }
   ibo.unmap();

   vao.enableVertexAttributeArray(0);
   vao.vertexAttributePointer(0, 3, VAO::FLOAT, false, vbo.elementSize(), 0);

   vao.enableVertexAttributeArray(1);
   vao.vertexAttributePointer(1, 3, VAO::FLOAT, false, vbo.elementSize(), 3*sizeof(float));

   vao.enableVertexAttributeArray(2);
   vao.vertexAttributePointer(2, 3, VAO::FLOAT, false, vbo.elementSize(), 6*sizeof(float));

   vao.enableVertexAttributeArray(3);
   vao.vertexAttributePointer(3, 2, VAO::FLOAT, false, vbo.elementSize(), 9*sizeof(float));
}

void Sphere::render(Mat4f const & vpMat, Mat4f const & vMat, double deltaTime) {
   angle += deltaTime*15.0; // rotate by 15 degree per second
   if (angle > 360.0) angle -= 360.0;

   if (!program || !texture || !normalMap) return;

   glEnable(GL_PRIMITIVE_RESTART);
   glPrimitiveRestartIndex(65535);
   vao.bind();
   vbo.bind();
   ibo.bind();
   texture->bindToTIU(0);
   normalMap->bindToTIU(1);
   program->use();
   Mat4f rot = Mat4f::rotation(angle, Vec3f(0.0f, 1.0f, 0.0f)) *
               Mat4f::rotation(90.0, Vec3f(1.0f, 0.0f, 0.0f));
   program->setUniform("mv", vMat*rot*modelMat);
   program->setUniform("v", vMat);
   program->setUniform("mvp", vpMat*rot*modelMat);
   ibo.draw(BufferObject::TRIANGLE_STRIP);
   glDisable(GL_PRIMITIVE_RESTART);
}

void Sphere::renderAndSave(Mat4f const & vpMat, Mat4f const & vMat) {
   Size2i size(1024, 1024);

   Texture2D tex;
   tex.bind();
   tex.createStorage(size, 1);

   RenderbufferObject rbo;
   rbo.bind();
   rbo.createStorage(size);

   FramebufferObject fbo;
   fbo.bind(FBO::DRAW);
   fbo.attach(tex);
   fbo.attach(rbo);
   fbo.setViewport(size);
   fbo.clear(true, true);
   //std::cout << fbo.getStatusString();

   render(Mat4f::perspective(45.0, size.aspectRatio(), 0.1f, 10.0f) * vMat, vMat);

   tex.bind();
   tex.getImage().savePNG("spheretest.png");

   fbo.unbind();
}
