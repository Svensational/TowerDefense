#include "texture2d.h"
#include <cmath>
#include "gl_core_4_4.h"

Texture2D::Texture2D() :
   Texture(TEXTURE_2D), created(false), size(0, 0), levels(0)
{
}

Texture2D::Texture2D(Texture2D && other) :
   Texture(other.name, other.target), created(other.created), size(other.size), levels(other.levels)
{
   other.name = 0;
}

bool Texture2D::createStorage(Size2i size, int levels) {
   if (created) {
      return false;
   }

   // levels = -1 means max mipmap level according to texture dimensions
   const int maxLevels = ilogb(size.max())+1;
   if (levels == 0) levels = 1;
   if (levels < 0 || levels > maxLevels) levels = maxLevels;

   this->size = size;
   this->levels = levels;

   if (glTexStorage2D) {
      // try to allocate immutable storage (ogl 4.3)
      glTexStorage2D(target, levels, GL_RGBA8, size.width, size.height);
   }
   else {
      // ensure texture completeness despite mutable storage
      for (int i=0; i<levels; ++i) {
         glTexImage2D(target, i, GL_RGBA8, size.width, size.height, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);
         size = Size2i(std::max(1, size.width>>1),
                       std::max(1, size.height>>1));
      }
      glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, levels-1);
   }

   return created = true;
}

void Texture2D::generateMipmaps() const {
   glGenerateMipmap(target);
}

Image Texture2D::getImage(int level) const {
   Image image(getSize(level));
   if (created) {
      glGetTexImage(target, level, GL_BGRA, GL_UNSIGNED_BYTE, image.rawData());
   }
   return image;
}

Size2i Texture2D::getSize(int level) const {
   if (level<0) level = 0;
   return Size2i(std::max(size.width>>level, 1),
                 std::max(size.height>>level, 1));
}

bool Texture2D::isCreated() const {
   return created;
}

Texture2D & Texture2D::operator =(Texture2D && other) {
   std::swap(name, other.name);
   target = other.target;
   created = other.created;
   size = other.size;
   levels = other.levels;
   return *this;
}

void Texture2D::setImage(Image const & image, int level) const {
   setSubImage(0, 0, image, level);
}

void Texture2D::setSubImage(int xOffset, int yOffset, Image const & image, int level) const {
   glTexSubImage2D(target, level, xOffset, yOffset,
                   image.getWidth(), image.getHeight(),
                   GL_BGRA, GL_UNSIGNED_BYTE, image.rawData());
}

void Texture2D::setWrapHeuristics(WrapHeuristic heuristic) const {
   glTexParameteri(target, GL_TEXTURE_WRAP_S, heuristic);
   glTexParameteri(target, GL_TEXTURE_WRAP_T, heuristic);
}

void Texture2D::setWrapHeuristics(WrapHeuristic heuristicS, WrapHeuristic heuristicT) const {
   glTexParameteri(target, GL_TEXTURE_WRAP_S, heuristicS);
   glTexParameteri(target, GL_TEXTURE_WRAP_T, heuristicT);
}
