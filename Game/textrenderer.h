#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H
#include <unordered_map>

class Mat4f;
class Text;
class ProgramObject;

class TextRenderer {

public:
   TextRenderer();
   virtual ~TextRenderer();
   void addText(Text * text);
   void render(Mat4f const & vpMat) const;

private:
   std::unordered_multimap<std::string, Text*> texts;
   ProgramObject * program;
   int textColorLocation;
   int mvpLocation;

   void init();
};

#endif // TEXTRENDERER_H
