#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <sstream>
#include "mat4f.h"
#include "vertex.h"

class VertexArrayObject;
template <typename T> class VertexBufferObject;
template <typename T> class IndexBufferObject;

class Text {

   friend class TextRenderer;

public:
   Text(std::string const & fontname, std::u32string const & text = std::u32string());
   void setString(std::u32string const & text);
   void setString(std::string const & text);
   virtual ~Text();

private:
   bool dynamicHint;
   std::u32string string;
   Mat4f modelMat;
   std::string fontname;
   VertexArrayObject * vao;
   VertexBufferObject<Pos2f_Tex2f> * vbo;
   IndexBufferObject<unsigned short> * ibo;

   void init();
   void render();
};

template <typename T>
std::u32string toU32String(T const & value) {
   std::stringstream stream;
   stream << value;
   std::u32string string = U"";
   for (char c : stream.str()) {
      string += char32_t(c);
   }
   return string;
}

#endif // TEXT_H
