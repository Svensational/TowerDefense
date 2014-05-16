#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "mat4f.h"
#include "vertex.h"

class Font;
class VertexArrayObject;
template <typename T> class VertexBufferObject;
template <typename T> class IndexBufferObject;

class Text {

   friend class TextRenderer;

public:
   Text(std::u32string const & text, Font * font);
   virtual ~Text();

private:
   std::u32string string;
   Mat4f modelMat;
   Font * font;
   VertexArrayObject * vao;
   VertexBufferObject<Pos2f_Tex2f> * vbo;
   IndexBufferObject<unsigned short> * ibo;

   void init();
   void createBuffers();
   void render();
};

#endif // TEXT_H
