#ifndef FONT_H
#define FONT_H
#include <string>

struct FT_LibraryRec_;
struct FT_FaceRec_;

class Font {

public:
   explicit Font(std::string filename);
   virtual ~Font();

private:
   static FT_LibraryRec_ * library;
   FT_FaceRec_ * face;

   void testRender(char testChar);
};

#endif // FONT_H
