#include "font.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "image.h"
#include "texture2d.h"
#include <iostream>

FT_Library Font::library = nullptr;

Font::Font(std::string filename, int pixelSize) :
   face(nullptr), pixelSize(pixelSize), image(Size2i(2048, 1024))
{
   if (!library) {
      // initialize library
      FT_Init_FreeType(&library);
   }
   // load font face from file
   FT_New_Face(library, filename.c_str(), 0, &face);
   // set pixel size
   FT_Set_Pixel_Sizes(face, 0, pixelSize);
   // init with common glyphs
   init();

   // TESTRENDER!
   image.savePNG("fonttest.png");
}

Font::~Font() {
   FT_Done_Face(face);
}

void Font::addGlyph(unsigned int unicode) {
   static int penX = 0;
   static int penY = 0;
   static int lineHeight = 0;
   const int spacing = pixelSize>>3;
   FT_GlyphSlot slot = face->glyph;

   // load freeType glyph
   FT_Load_Char(face, unicode, FT_LOAD_RENDER);

   // if line is full switch to next line
   if (penX+slot->bitmap.width > image.getWidth()) {
      penX = 0;
      penY += lineHeight + spacing;
      lineHeight = 0;
   }

   // create own glyph struct
   Glyph glyph;
   glyph.pos = Rectf(slot->bitmap_left / float(pixelSize),
                     (slot->bitmap_top-slot->bitmap.rows) / float(pixelSize),
                     slot->bitmap.width / float(pixelSize),
                     slot->bitmap.rows / float(pixelSize));
   glyph.tex = Rectf(penX / float(image.getWidth()),
                     penY / float(image.getHeight()),
                     slot->bitmap.width / float(image.getWidth()),
                     slot->bitmap.rows / float(image.getHeight()));
   glyph.advance = Vec2f(slot->advance.x / float(pixelSize),
                         slot->advance.y / float(pixelSize));

   Image::Rgba * target = reinterpret_cast<Image::Rgba *>(image.rawData())
                          + penY*image.getWidth() + penX;
   unsigned char * src = slot->bitmap.buffer;
   if (slot->bitmap.pitch > 0) src += slot->bitmap.pitch*(slot->bitmap.rows-1);

   // copy rendered freeType glyph to image
   for (int y=0; y<slot->bitmap.rows; ++y) {
      for (int x=0; x<slot->bitmap.width; ++x) {
         *(target+x) = Image::Rgba(255, 255, 255, *(src+x));
      }
      target += image.getWidth();
      src -= slot->bitmap.pitch;
   }

   penX += slot->bitmap.width + spacing;
   lineHeight = std::max(lineHeight, slot->bitmap.rows);

   // insert glyph into glyph map
   glyphs.insert(std::pair<unsigned int, Glyph>(unicode, glyph));
}

Font::Glyph const & Font::getGlyph(unsigned int unicode) {
   if (!glyphs.count(unicode)) {
      addGlyph(unicode);
   }
   return glyphs[unicode];
}

float Font::getKerning(unsigned int a, unsigned int b) {
   if (!kernings.count(std::pair<unsigned int, unsigned int>(a, b))) {
      FT_Vector kerning;
      FT_Get_Kerning(face, FT_Get_Char_Index(face, a), FT_Get_Char_Index(face, b), FT_KERNING_UNFITTED, &kerning);
      kernings.insert(std::pair<std::pair<unsigned int, unsigned int>, float>(std::pair<unsigned int, unsigned int>(a, b), kerning.x/(64.0f*pixelSize)));
   }
   return kernings[std::pair<unsigned int, unsigned int>(a, b)];
}

void Font::init() {
   for (int i=32; i<127; ++i) {
      addGlyph(i);
   }
}
