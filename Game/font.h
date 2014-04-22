#ifndef FONT_H
#define FONT_H
#include <string>
#include <map>
#include "image.h"

struct FT_LibraryRec_;
struct FT_FaceRec_;

class Font {

   struct Glyph {
      float xMin, xMax;
      float yMin, yMax;
      float sMin, sMax;
      float tMin, tMax;
      float advance;
   };

public:
   explicit Font(std::string filename, int pixelSize = 128);
   virtual ~Font();
   Glyph const & getGlyph(unsigned int unicode);
   float getKerning(unsigned int a, unsigned int b);

private:
   FT_FaceRec_ * face;
   int pixelSize;
   Image image;
   std::map<unsigned int, Glyph> glyphs;
   std::map<std::pair<unsigned int, unsigned int>, float> kernings;
   static FT_LibraryRec_ * library;

   void init();
   void addGlyph(unsigned int unicode);
};

#endif // FONT_H
