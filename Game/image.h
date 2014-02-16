#ifndef IMAGE_H
#define IMAGE_H
#include "size2i.h"

class Image {

public:
   Image();
   Image(Image && other);
   virtual ~Image();
   Image & operator =(Image && other);

   bool loadPNG(std::string const & filename);
   bool savePNG(std::string const & filename) const;

   bool isNull() const;
   Size2i getSize() const;
   int getWidth() const;
   int getHeight() const;
   unsigned char const * const getData() const;

private:
   Size2i size;
   unsigned char * data;
};

#endif // IMAGE_H
