#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include "vec.h"

class Image {

public:

   struct Ga {
      unsigned char g, a;

      Ga(unsigned char g, unsigned char a) :
         g(g), a(a)
      {}
   };

   struct Rgb {
      unsigned char r, g, b;

      Rgb(unsigned char r, unsigned char g, unsigned char b) :
         r(r), g(g), b(b)
      {}
   };

   struct Bgr {
      unsigned char b, g, r;

      Bgr(unsigned char b, unsigned char g, unsigned char r) :
         b(b), g(g), r(r)
      {}
   };

   struct Rgba {
      unsigned char r, g, b, a;

      Rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
         r(r), g(g), b(b), a(a)
      {}
   };

   struct Bgra {
      unsigned char b, g, r, a;

      Bgra(unsigned char b, unsigned char g, unsigned char r, unsigned char a) :
         b(b), g(g), r(r), a(a)
      {}
   };

   enum Format {
      GRAY,
      GA,
      RGB,
      BGR,
      RGBA,
      BGRA
   };

   explicit Image(Format format = BGRA, Size2i size = Size2i(), unsigned char * data = nullptr);
   Image(Image && other);
   virtual ~Image();
   Image & operator =(Image && other);

   bool loadPNG(std::string const & filename);
   bool savePNG(std::string const & filename) const;

   bool isNull() const;
   unsigned int channelCount() const;
   Size2i getSize() const;
   int getWidth() const;
   int getHeight() const;
   unsigned char * rawData();
   unsigned char const * const rawData() const;

private:
   Format format;
   Size2i size;
   unsigned char * data;

   unsigned int pngFormat() const;
};

#endif // IMAGE_H
