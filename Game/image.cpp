#include "image.h"
#include <cstring>
#include <png.h>

Image::Image() :
   size(0, 0), data(nullptr)
{
}

Image::Image(Image && other) :
   size(other.size), data(other.data)
{
   other.data = nullptr;
}

Image::~Image() {
   delete[] data;
}

unsigned char const * const Image::getData() const {
   return data;
}

int Image::getHeight() const {
   return size.height();
}

Size2i Image::getSize() const {
   return size;
}

int Image::getWidth() const {
   return size.width();
}

bool Image::isNull() const {
   return !data;
}

bool Image::loadPNG(std::string const & filename) {
   png_image image;
   memset(&image, 0, sizeof(image));
   image.version = PNG_IMAGE_VERSION;

   if (!png_image_begin_read_from_file(&image, filename.c_str())) {
      return false;
   }

   png_bytep buffer;
   // on most systems BGRA is preferred for pixel upload
   image.format = PNG_FORMAT_BGRA;
   buffer = new png_byte[PNG_IMAGE_SIZE(image)];

   // a negative stride indicates that the bottom-most row is first in the buffer
   // (as expected by openGL)
   if (!png_image_finish_read(&image, nullptr, buffer, -image.width*4, nullptr)) {
      png_image_free(&image);
      return false;
   }

   size = Size2i(image.width, image.height);
   data = buffer;
   return true;
}

Image & Image::operator =(Image && other) {
   size = other.size;
   std::swap(data, other.data);
   return *this;
}

bool Image::savePNG(std::string const & filename) const {
   if (!data) {
      return false;
   }

   png_image image;
   memset(&image, 0, sizeof(image));
   image.version = PNG_IMAGE_VERSION;
   image.width = size.width();
   image.height = size.height();
   image.format = PNG_FORMAT_BGRA;

   return png_image_write_to_file(&image, filename.c_str(), 0,
                                  data, -image.width*4, nullptr);
}
