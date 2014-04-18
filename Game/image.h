#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include "size2i.h"

class Image {

public:

   struct Rgba {
      unsigned char r;
      unsigned char g;
      unsigned char b;
      unsigned char a;

      Rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
   };

   Image();
   explicit Image(Size2i size, unsigned char * data = nullptr);
   Image(Image && other);
   virtual ~Image();
   Image & operator =(Image && other);

   bool loadPNG(std::string const & filename);
   bool savePNG(std::string const & filename) const;

   bool isNull() const;
   Size2i getSize() const;
   int getWidth() const;
   int getHeight() const;
   unsigned char * rawData();
   unsigned char const * const rawData() const;

private:
   Size2i size;
   unsigned char * data;
};

#endif // IMAGE_H
