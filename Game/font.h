#ifndef FONT_H
#define FONT_H
#include <string>
#include <map>
#include "vec.h"

struct FT_LibraryRec_;
struct FT_FaceRec_;
class Image;
class Texture2D;

class Font {

public:
   struct Glyph {
      Rectf pos;
      Rectf tex;
      Vec2f advance;
   };

   explicit Font(std::string const & filename, int pixelSize = 128);
   virtual ~Font();
   Glyph const & getGlyph(unsigned int unicode);
   Vec2f getKerning(unsigned int a, unsigned int b);
   void bindToTIU(unsigned short textureImageUnit) const;

private:
   int pixelSize;
   FT_FaceRec_ * face;
   Image * image;
   Texture2D * texture;
   std::map<unsigned int, Glyph> glyphs;
   std::map<std::pair<unsigned int, unsigned int>, Vec2f> kernings;
   static FT_LibraryRec_ * library;

   void init(std::string const & filename);
   void initMap();
   void addGlyph(unsigned int unicode);
};

#endif // FONT_H
