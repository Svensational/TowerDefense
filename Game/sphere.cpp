#include "sphere.h"
#include <cmath>
#include "gl_core_4_4.h"
#include "shaderobject.h"
#include "renderbufferobject.h"
#include "framebufferobject.h"
#include <iostream>

Sphere::Sphere(Point3f const & pos, float size) :
   angle(0.0f),
   modelMat(Mat4f::translation(Vec3f(pos)) * Mat4f::scaling(size, size, size))
{
   loadTexture();
   loadProgram();
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
         iv->ver = {float(sin(theta)*cos(phi)), float(sin(theta)*sin(phi)), float(cos(theta))};
         iv->nor = iv->ver;
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
   vao.vertexAttributePointer(0, 3, GL_FLOAT, false, vbo.elementSize(), 0);

   vao.enableVertexAttributeArray(1);
   vao.vertexAttributePointer(1, 3, GL_FLOAT, false, vbo.elementSize(), 3*sizeof(float));

   vao.enableVertexAttributeArray(2);
   vao.vertexAttributePointer(2, 3, GL_FLOAT, false, vbo.elementSize(), 6*sizeof(float));

   vao.enableVertexAttributeArray(3);
   vao.vertexAttributePointer(3, 2, GL_FLOAT, false, vbo.elementSize(), 9*sizeof(float));
}

void Sphere::loadProgram() {
   ShaderObject vertexShader(ShaderObject::VERTEX_SHADER);
   vertexShader.loadSource("shaders/normalmapped.vertex.glsl");
   vertexShader.compile();
   std::cout << vertexShader.getLog() << std::endl;

   ShaderObject fragmentShader(ShaderObject::FRAGMENT_SHADER);
   fragmentShader.loadSource("shaders/normalmapped.fragment.glsl");
   fragmentShader.compile();
   std::cout << fragmentShader.getLog() << std::endl;

   program.attachShader(vertexShader);
   program.attachShader(fragmentShader);
   program.link();
   std::cout << program.getLog() << std::endl;
   program.detachShader(vertexShader);
   program.detachShader(fragmentShader);

   program.use();
   program.setUniform("lightDir", Vec3f(1.0f, -1.0f, -1.0f));
   program.setUniform("lightColor", Vec3f(1.0f, 1.0f, 1.0f));
   program.setUniform("textureSampler", 0);
   program.setUniform("normalMapSampler", 1);
}

void Sphere::loadTexture() {
   Image image;
   image.loadPNG("images/test.png");
   texture.bind();
   texture.createStorage(image.getSize());
   texture.setImage(image);
   texture.generateMipmaps();
   texture.setMinFilter(Texture::LINEAR, Texture::LINEAR);
   texture.setMagFilter(Texture::LINEAR);
   texture.setMaxAnisotropy();

   image.loadPNG("images/test_n.png");
   normalMap.bind();
   normalMap.createStorage(image.getSize());
   normalMap.setImage(image);
   normalMap.generateMipmaps();
   normalMap.setMinFilter(Texture::LINEAR, Texture::LINEAR);
   normalMap.setMagFilter(Texture::LINEAR);
   normalMap.setMaxAnisotropy();
}

void Sphere::render(Mat4f const & vpMat, Mat4f const & vMat, double deltaTime) {
   angle += deltaTime*15.0f; // rotate by 15 degree per second
   if (angle > 360.0) angle -= 360.0;

   glEnable(GL_PRIMITIVE_RESTART);
   glPrimitiveRestartIndex(65535);
   vao.bind();
   vbo.bind();
   ibo.bind();
   texture.bindToTIU(0);
   normalMap.bindToTIU(1);
   program.use();
   Mat4f rot = Mat4f::rotation(angle, Vec3f(0.0f, 1.0f, 0.0f)) *
               Mat4f::rotation(90.0, Vec3f(1.0f, 0.0f, 0.0f));
   program.setUniform("mv", vMat*rot*modelMat);
   program.setUniform("v", vMat);
   program.setUniform("mvp", vpMat*rot*modelMat);
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
