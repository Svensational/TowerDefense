#include "image.h"
#include <cstring>
#include <png.h>

Image::Image(Format format, Size2i size, unsigned char * data) :
   format(format), size(size), data(nullptr)
{
   if (size.area()) {
      this->data = new unsigned char[size.area()*channelCount()];
      if (data) {
         memcpy(this->data, data, size.area()*channelCount());
      }
      /*else {
         memset(this->data, 0u, size.area()*channelCount());
      }*/
   }
}

Image::Image(Image && other) :
   format(other.format), size(other.size), data(other.data)
{
   other.data = nullptr;
}

Image::~Image() {
   delete[] data;
}

unsigned int Image::channelCount() const {
   switch (format) {
      case GRAY:
         return 1u;
      case GA:
         return 2u;
      case RGB:
      case BGR:
         return 3u;
      case RGBA:
      case BGRA:
         return 4u;
      default:
         return 0u;
   }
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
   image.format = pngFormat();
   buffer = new png_byte[PNG_IMAGE_SIZE(image)];

   // a negative stride indicates that the bottom-most row is first in the buffer
   // (as expected by openGL)
   if (!png_image_finish_read(&image, nullptr, buffer, -image.width*channelCount(), nullptr)) {
      png_image_free(&image);
      return false;
   }

   size = Size2i(image.width, image.height);
   delete[] data;
   data = buffer;
   return true;
}

Image & Image::operator =(Image && other) {
   format = other.format;
   size = other.size;
   std::swap(data, other.data);
   return *this;
}

unsigned int Image::pngFormat() const {
   switch (format) {
      case GRAY:
         return PNG_FORMAT_GRAY;
      case GA:
         return PNG_FORMAT_GA;
      case RGB:
         return PNG_FORMAT_RGB;
      case BGR:
         return PNG_FORMAT_BGR;
      case RGBA:
         return PNG_FORMAT_RGBA;
      case BGRA:
         // on most systems BGRA is preferred for pixel upload
         return PNG_FORMAT_BGRA;
      default:
         return 0u;
   }
}

unsigned char * Image::rawData() {
   return data;
}

unsigned char const * const Image::rawData() const {
   return data;
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
   image.format = pngFormat();

   return png_image_write_to_file(&image, filename.c_str(), 0,
                                  data, -image.width*channelCount(), nullptr);
}
