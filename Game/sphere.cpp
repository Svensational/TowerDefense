#include "sphere.h"
#include "shaderobject.h"
#include "gl_core_4_4.h"
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
   vao.bind();
   vbo.bind();

   vbo.createStorage(BufferObject::STATIC_DRAW, 6);
   Vertex_V3F_N3F_T2F * iv = vbo.map(BufferObject::WRITE_ONLY);
   iv->v = {1.0f, 0.0f, 0.0f};
   iv->n = {1.0f, 0.0f, 0.0f};
   iv->t = {1.0f, 0.5f};
   ++iv;
   iv->v = {-1.0f, 0.0f, 0.0f};
   iv->n = {-1.0f, 0.0f, 0.0f};
   iv->t = {0.0f, 0.5f};
   ++iv;
   iv->v = {0.0f, 1.0f, 0.0f};
   iv->n = {0.0f, 1.0f, 0.0f};
   iv->t = {0.5f, 1.0f};
   ++iv;
   iv->v = {0.0f, -1.0f, 0.0f};
   iv->n = {0.0f, -1.0f, 0.0f};
   iv->t = {0.5f, 0.0f};
   ++iv;
   iv->v = {0.0f, 0.0f, 1.0f};
   iv->n = {0.0f, 0.0f, 1.0f};
   iv->t = {0.5f, 0.5f};
   ++iv;
   iv->v = {0.0f, 0.0f, -1.0f};
   iv->n = {0.0f, 0.0f, -1.0f};
   iv->t = {0.5f, 0.5f};
   vbo.unmap();

   ibo.bind();
   ibo.createStorage(BufferObject::STATIC_DRAW, 24);
   unsigned char * ii = ibo.map(BufferObject::WRITE_ONLY);
   *ii++ = 0;
   *ii++ = 4;
   *ii++ = 2;
   *ii++ = 4;
   *ii++ = 1;
   *ii++ = 2;
   *ii++ = 1;
   *ii++ = 5;
   *ii++ = 2;
   *ii++ = 5;
   *ii++ = 0;
   *ii++ = 2;
   *ii++ = 0;
   *ii++ = 5;
   *ii++ = 3;
   *ii++ = 5;
   *ii++ = 1;
   *ii++ = 3;
   *ii++ = 1;
   *ii++ = 4;
   *ii++ = 3;
   *ii++ = 4;
   *ii++ = 0;
   *ii++ = 3;
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
   program.setUniform("textureSampler", 0/*texture image unit*/);
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
   vao.bind();
   vbo.bind();
   ibo.bind();
   program.use();
   program.setUniform("m", modelMat);
   program.setUniform("v", vMat);
   program.setUniform("mvp", vpMat*modelMat);
   ibo.draw(BufferObject::TRIANGLES);
}
