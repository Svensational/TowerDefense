#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "mat4f.h"
#include "vertexarrayobject.h"
#include "vertexbufferobject.h"
#include "indexbufferobject.h"
#include "programobject.h"
#include "vertex.h"

class Font;

class Text {

public:
   Text(std::u32string const & text, Font * font);
   virtual ~Text();
   void render(Mat4f const & vpMat);

private:
   std::u32string string;
   Mat4f modelMat;
   VAO vao;
   VBO<Pos2f_Tex2f> vbo;
   IBOus ibo;
   ProgramObject program;
   Font * font;

   void createBuffers();
   void loadProgram();
};

#endif // TEXT_H
