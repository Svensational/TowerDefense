#include "text.h"
#include "font.h"
#include "gl_core_4_4.h"
#include "shaderobject.h"
#include <iostream>

Text::Text(std::u32string const & text, Font * font) :
   string(text), font(font)
{
   // just for testing
   string += char32_t('T');
   string += char32_t('e');
   string += char32_t('s');
   string += char32_t('t');
   loadProgram(); // will be moved to a global ressource manager or something
   createBuffers();
}

Text::~Text() {
}

void Text::createBuffers() {
   vao.bind();

   vbo.bind();
   vbo.createStorage(BufferObject::STATIC_DRAW, string.size()*4);
   auto * iv = vbo.map(BufferObject::WRITE_ONLY);
   Font::Glyph glyph;
   Point2f pen(0.0f, 0.0f);
   for (unsigned int i=0; i<=string.size(); ++i) {
      if (i>0) {
         pen += font->getKerning(string[i-1], string[i]);
      }

      glyph = font->getGlyph(string[i]);

      iv->pos = pen + Vec2f(glyph.pos.lowerLeft());
      iv->tex = glyph.tex.lowerLeft();
      ++iv;

      iv->pos = pen + Vec2f(glyph.pos.lowerRight());
      iv->tex = glyph.tex.lowerRight();
      ++iv;

      iv->pos = pen + Vec2f(glyph.pos.upperRight());
      iv->tex = glyph.tex.upperRight();
      ++iv;

      iv->pos = pen + Vec2f(glyph.pos.upperLeft());
      iv->tex = glyph.tex.upperLeft();
      ++iv;

      pen += glyph.advance;
   }
   vbo.unmap();

   ibo.bind();
   ibo.createStorage(BufferObject::STATIC_DRAW, string.size()*5);
   auto * ii = ibo.map(BufferObject::WRITE_ONLY);
   for (unsigned int i=0; i<=string.size(); ++i) {
      *ii++ = i*4 + 3;
      *ii++ = i*4 + 0;
      *ii++ = i*4 + 2;
      *ii++ = i*4 + 1;
      *ii++ = 65535;
   }
   ibo.unmap();

   vao.enableVertexAttributeArray(0);
   vao.vertexAttributePointer(0, 2, GL_FLOAT, false, vbo.elementSize(), 0);

   vao.enableVertexAttributeArray(3);
   vao.vertexAttributePointer(3, 2, GL_FLOAT, false, vbo.elementSize(), 2*sizeof(float));
}

void Text::loadProgram() {
   ShaderObject vertexShader(ShaderObject::VERTEX_SHADER);
   vertexShader.loadSource("shaders/text.vertex.glsl");
   vertexShader.compile();
   //std::cout << vertexShader.getLog() << std::endl;

   ShaderObject fragmentShader(ShaderObject::FRAGMENT_SHADER);
   fragmentShader.loadSource("shaders/text.fragment.glsl");
   fragmentShader.compile();
   //std::cout << fragmentShader.getLog() << std::endl;

   program.attachShader(vertexShader);
   program.attachShader(fragmentShader);
   program.link();
   //std::cout << program.getLog() << std::endl;
   program.detachShader(vertexShader);
   program.detachShader(fragmentShader);

   program.use();
   program.setUniform("textTexture", 0);
}

void Text::render(Mat4f const & vpMat) {
   glEnable(GL_PRIMITIVE_RESTART);
   glPrimitiveRestartIndex(65535);
   vao.bind();
   vbo.bind();
   ibo.bind();
   font->bindToTIU(0);
   program.use();
   program.setUniform("textColor", Vec3f(1.0f, 0.5f, 0.5f));
   program.setUniform("mvp", vpMat*modelMat);
   ibo.draw(BufferObject::TRIANGLE_STRIP);
   glDisable(GL_PRIMITIVE_RESTART);
}
