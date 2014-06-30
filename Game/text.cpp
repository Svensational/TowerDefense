#include "text.h"
#include "vertexarrayobject.h"
#include "vertexbufferobject.h"
#include "indexbufferobject.h"
#include "font.h"
#include "resourcemanager.h"

Text::Text(Mat4f const & transformation, std::string const & fontname, std::u32string const & text) :
   dynamicHint(text.empty()), modelMat(transformation),
   fontname(fontname), string(text),
   vao(nullptr), vbo(nullptr), ibo(nullptr)
{
   init();
}

Text::~Text() {
   delete vao;
   delete ibo;
   delete vbo;
}

void Text::init() {
   vbo = new VBO<Pos2f_Tex2f>();
   ibo = new IBO<unsigned short>();

   if (!string.empty()) {
      setString(string);
   }
   else {
      vbo->bind();
   }

   // init VAO
   vao = new VertexArrayObject();
   vao->bind();

   vao->enableVertexAttributeArray(0);
   vao->vertexAttributePointer(0, 2, VAO::FLOAT, false, vbo->elementSize(), 0);

   vao->enableVertexAttributeArray(3);
   vao->vertexAttributePointer(3, 2, VAO::FLOAT, false, vbo->elementSize(), 2*sizeof(float));
}

void Text::render() {
   vao->bind();
   ibo->bind();
   ibo->draw(BufferObject::TRIANGLE_STRIP, string.size()*5);
}

void Text::setString(std::string const & text) {
   std::u32string string = U"";
   for (char c : text) {
      string += char32_t(c);
   }
   setString(string);
}

void Text::setString(std::u32string const & text) {
   string = text;
   vbo->bind();
   ibo->bind();

   Font * font = ResourceManager::getGlobalInstance()->getFont(fontname);
   if (!font) return;

   if (string.size()*5 > ibo->getCount()) {
      // (re)create buffers
      // funny thing, but my 8GB RAM / 4GB VRAM rig runs out of memory when hint is STATIC_DRAW
      BufferObject::Usage usage = BufferObject::DYNAMIC_DRAW;//dynamicHint ? BufferObject::DYNAMIC_DRAW : BufferObject::STATIC_DRAW;
      vbo->createStorage(usage, string.size()*4);
      ibo->createStorage(usage, string.size()*5);
   }

   // set buffer content
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

   auto * ii = ibo->map(BufferObject::WRITE_ONLY);
   for (unsigned int i=0; i<=string.size(); ++i) {
      *ii++ = i*4 + 3;
      *ii++ = i*4 + 0;
      *ii++ = i*4 + 2;
      *ii++ = i*4 + 1;
      *ii++ = 65535u;
   }
   ibo->unmap();
}
