#include "text.h"
#include "font.h"
#include "gl_core_4_4.h"
#include "vertexarrayobject.h"
#include "vertexbufferobject.h"
#include "indexbufferobject.h"

Text::Text(std::u32string const & text, Font * font) :
   string(text), font(font), vao(nullptr), vbo(nullptr), ibo(nullptr)
{
   // just for testing
   string += char32_t('T');
   string += char32_t('e');
   string += char32_t('s');
   string += char32_t('t');

   init();
}

Text::~Text() {
   delete vao;
   delete ibo;
   delete vbo;
}

void Text::createBuffers() {
   vbo->bind();
   vbo->createStorage(BufferObject::STATIC_DRAW, string.size()*4);
   auto * iv = vbo->map(BufferObject::WRITE_ONLY);
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
   vbo->unmap();

   ibo->bind();
   ibo->createStorage(BufferObject::STATIC_DRAW, string.size()*5);
   auto * ii = ibo->map(BufferObject::WRITE_ONLY);
   for (unsigned int i=0; i<=string.size(); ++i) {
      *ii++ = i*4 + 3;
      *ii++ = i*4 + 0;
      *ii++ = i*4 + 2;
      *ii++ = i*4 + 1;
      *ii++ = 65535;
   }
   ibo->unmap();

   // init VAO
   vao = new VertexArrayObject();
   vao->bind();

   vao->enableVertexAttributeArray(0);
   vao->vertexAttributePointer(0, 2, GL_FLOAT, false, vbo->elementSize(), 0);

   vao->enableVertexAttributeArray(3);
   vao->vertexAttributePointer(3, 2, GL_FLOAT, false, vbo->elementSize(), 2*sizeof(float));
}

void Text::init() {
   vbo = new VBO<Pos2f_Tex2f>();
   ibo = new IBO<unsigned short>();

   createBuffers();
}

void Text::render() {
   vao->bind();
   ibo->bind();
   ibo->draw(BufferObject::TRIANGLE_STRIP);
}
