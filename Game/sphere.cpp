#include "sphere.h"
#include <cmath>
#include "gl_core_4_4.h"
#include "shaderobject.h"
#include <iostream>

Sphere::Sphere(Point3f const & pos, float size) :
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
   Vertex_V3F_N3F_T2F * iv = vbo.map(BufferObject::WRITE_ONLY);
   for (int i=0; i<=n; ++i) {
      theta = (i*pi)/double(n);
      for (int j=0; j<2*n; ++j) {
         phi = (j*pi)/double(n);
         iv->v = {float(sin(theta)*cos(phi)), float(sin(theta)*sin(phi)), -float(cos(theta))};
         iv->n = iv->v;
         iv->t = {std::abs(j/float(n)-1.0f), i/float(n)};
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
   vao.vertexAttributePointer(0, 3, GL_FLOAT, false, sizeof(Vertex_V3F_N3F_T2F), 0);

   vao.enableVertexAttributeArray(1);
   vao.vertexAttributePointer(1, 3, GL_FLOAT, false, sizeof(Vertex_V3F_N3F_T2F), 3*sizeof(float));

   vao.enableVertexAttributeArray(3);
   vao.vertexAttributePointer(3, 2, GL_FLOAT, false, sizeof(Vertex_V3F_N3F_T2F), 6*sizeof(float));
}

void Sphere::loadProgram() {
   ShaderObject vertexShader(ShaderObject::VERTEX_SHADER);
   vertexShader.loadSource("shaders/default.vertex.glsl");
   vertexShader.compile();
   std::cout << vertexShader.getLog() << std::endl;

   ShaderObject fragmentShader(ShaderObject::FRAGMENT_SHADER);
   fragmentShader.loadSource("shaders/default.fragment.glsl");
   fragmentShader.compile();
   std::cout << fragmentShader.getLog() << std::endl;

   program.attachShader(vertexShader);
   program.attachShader(fragmentShader);
   program.link();
   std::cout << program.getLog() << std::endl;
   program.detachShader(vertexShader);
   program.detachShader(fragmentShader);

   program.use();
   program.setUniform("lightDir", Vec3f(-1.0f, 1.0f, -1.0f));
   program.setUniform("lightColor", Vec3f(1.0f, 1.0f, 1.0f));
   program.setUniform("textureSampler", 0);
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
}

void Sphere::render(Mat4f const & vpMat, Mat4f const & vMat) {
   glEnable(GL_PRIMITIVE_RESTART);
   glPrimitiveRestartIndex(65535);
   vao.bind();
   vbo.bind();
   ibo.bind();
   program.use();
   Mat4f rot = Mat4f::rotation(90.0f, Vec3f(1.0f, 0.0f, 0.0f));
   program.setUniform("mv", vMat*rot*modelMat);
   program.setUniform("v", vMat);
   program.setUniform("mvp", vpMat*rot*modelMat);
   ibo.draw(BufferObject::TRIANGLE_STRIP);
   glDisable(GL_PRIMITIVE_RESTART);
}
