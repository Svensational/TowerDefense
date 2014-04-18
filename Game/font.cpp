#include "font.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "image.h"
#include <iostream>

FT_Library Font::library = nullptr;

Font::Font(std::string filename) :
   face(nullptr)
{
   if (!library) {
      // initialize library
      FT_Init_FreeType(&library);
   }
   // load font face from file
   FT_New_Face(library, filename.c_str(), 0, &face);
   // set pixel size
   FT_Set_Pixel_Sizes(face, 0, 200);

   // TESTRENDER!
   testRender('Q');
}

Font::~Font() {
   FT_Done_Face(face);
}

void Font::testRender(char testChar) {
   FT_GlyphSlot slot = face->glyph;

   // load glyph
   FT_Load_Char(face, /*unicode*/testChar, FT_LOAD_RENDER);

   Image image(Size2i(slot->bitmap.width, slot->bitmap.rows));
   Image::Rgba * target = reinterpret_cast<Image::Rgba *>(image.rawData());
   unsigned char * src;

   for (int y=0; y<slot->bitmap.rows; ++y) {
      if (slot->bitmap.pitch < 0) {
         src = slot->bitmap.buffer - slot->bitmap.pitch*y;
      } else {
         src = slot->bitmap.buffer + slot->bitmap.pitch*(slot->bitmap.rows-1-y);
      }
      for (int x=0; x<slot->bitmap.width; ++x) {
         *target++ = Image::Rgba(255, 255, 255, *src++);
      }
   }

   image.savePNG("fonttest.png");
}
