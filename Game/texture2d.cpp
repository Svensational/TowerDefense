#include "texture2d.h"
#include <cmath>
#include "gl_core_4_4.h"

Texture2D::Texture2D() :
   Texture(TEXTURE_2D), created(false), channels(0), size(0, 0), levels(0)
{
}

Texture2D::Texture2D(Texture2D && other) :
   Texture(other.name, other.target), created(other.created),
   channels(other.channels), size(other.size), levels(other.levels)
{
   other.name = 0;
}

bool Texture2D::createStorage(Size2i size, unsigned int channels, int levels) {
   if (created) {
      return false;
   }

   // levels = -1 means max mipmap level according to texture dimensions
   const int maxLevels = ilogb(size.max())+1;
   if (levels == 0) levels = 1;
   if (levels < 0 || levels > maxLevels) levels = maxLevels;

   this->channels = std::min(std::max(1u, channels), 4u);
   this->size = size;
   this->levels = levels;

   if (glTexStorage2D) {
      // try to allocate immutable storage (ogl 4.3)
      glTexStorage2D(target, levels, glInternalFormat(), size.width(), size.height());
   }
   else {
      // ensure texture completeness despite mutable storage
      for (int i=0; i<levels; ++i) {
         glTexImage2D(target, i, glInternalFormat(), size.width(), size.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);
         size = Size2i(std::max(1, size.width()>>1),
                       std::max(1, size.height()>>1));
      }
      glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, levels-1);
   }

   return created = true;
}

void Texture2D::generateMipmaps() const {
   glGenerateMipmap(target);
}

Image Texture2D::getImage(int level) const {
   Image::Format format;
   switch (channels) {
      case 1:
         format = Image::GRAY;
         break;
      case 2:
         format = Image::GA;
         break;
      case 3:
         format = Image::BGR;
         break;
      case 4:
      default:
         format = Image::BGRA;
         break;
   }

   Image image(format, getSize(level));
   if (created) {
      glGetTexImage(target, level, glFormat(image.channelCount()), GL_UNSIGNED_BYTE, image.rawData());
   }
   return image;
}

Size2i Texture2D::getMaxSize() {
   static Size2i maxSize = getMaxSizePriv();
   return maxSize;
}

Size2i Texture2D::getMaxSizePriv() {
   int maxSize;
   glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxSize);
   return Size2i(maxSize, maxSize);
}

Size2i Texture2D::getSize(int level) const {
   if (level<0) level = 0;
   return Size2i(std::max(size.width()>>level, 1),
                 std::max(size.height()>>level, 1));
}

unsigned int Texture2D::glFormat(unsigned int channelCount) const {
   switch (channelCount) {
      case 1: return GL_RED;
      case 2: return GL_RG;
      case 3: return GL_BGR;
      case 4: return GL_BGRA;
      default: return 0u;
   }
}

unsigned int Texture2D::glInternalFormat(bool compressed) const {
   if (compressed) {
      switch (channels) {
         case 1: return GL_COMPRESSED_RED;
         case 2: return GL_COMPRESSED_RG;
         case 3: return GL_COMPRESSED_RGB;
         case 4: return GL_COMPRESSED_RGBA;
         default: return 0u;
      }
   }
   else {
      switch (channels) {
         case 1: return GL_R8;
         case 2: return GL_RG8;
         case 3: return GL_RGB8;
         case 4: return GL_RGBA8;
         default: return 0u;
      }
   }
}

bool Texture2D::isCreated() const {
   return created;
}

Texture2D & Texture2D::operator =(Texture2D && other) {
   std::swap(name, other.name);
   target = other.target;
   created = other.created;
   channels = other.channels;
   size = other.size;
   levels = other.levels;
   return *this;
}

void Texture2D::setImage(Image const & image, int level) const {
   setSubImage(Point2i(), image, level);
}

void Texture2D::setSubImage(Point2i const & offset, Image const & image, int level) const {
   glTexSubImage2D(target, level, offset[0], offset[1],
                   image.getWidth(), image.getHeight(),
                   glFormat(image.channelCount()), GL_UNSIGNED_BYTE,
                   image.rawData());
}

void Texture2D::setWrapHeuristics(WrapHeuristic heuristic) const {
   glTexParameteri(target, GL_TEXTURE_WRAP_S, heuristic);
   glTexParameteri(target, GL_TEXTURE_WRAP_T, heuristic);
}

void Texture2D::setWrapHeuristics(WrapHeuristic heuristicS, WrapHeuristic heuristicT) const {
   glTexParameteri(target, GL_TEXTURE_WRAP_S, heuristicS);
   glTexParameteri(target, GL_TEXTURE_WRAP_T, heuristicT);
}
