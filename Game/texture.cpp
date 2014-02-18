#include "texture.h"
#include "gl_core_4_4.h"

Texture::Texture(Target target) :
   name(0), target(target)
{
   glGenTextures(1, &name);
}

Texture::Texture(unsigned int name, Target target) :
   name(name), target(target)
{
}

Texture::~Texture() {
   glDeleteTextures(1, &name);
}

void Texture::bind() const {
   glBindTexture(target, name);
}

int Texture::getMaxAnisotropyMax() {
   static int maxAnisotropyMax = getMaxAnisotropyMaxPriv();
   return maxAnisotropyMax;
}

int Texture::getMaxAnisotropyMaxPriv() {
   float maxAnisotropyMax;
   // GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT = 0x84FF
   glGetFloatv(0x84FF, &maxAnisotropyMax);
   return maxAnisotropyMax;
}

int Texture::getMaxTextureImageUnits() {
   static int maxTextureImageUnits = getMaxTextureImageUnitsPriv();
   return maxTextureImageUnits;
}

int Texture::getMaxTextureImageUnitsPriv() {
   int maxTextureImageUnits;
   glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextureImageUnits);
   return maxTextureImageUnits;
}

void Texture::setActiveTextureImageUnit(int unit) {
   glActiveTexture(GL_TEXTURE0 + unit);
}

void Texture::setBorderColor(float r, float g, float b, float a) const {
   float color[4] = {r, g, b, a};
   glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, color);
}

void Texture::setMinFilter(Filter filter) const {
   glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter);
}

void Texture::setMinFilter(Filter filter, Filter mipmapFilter) const {
   int glFilter = GL_NEAREST_MIPMAP_NEAREST;
   if (filter == LINEAR) glFilter += 1;
   if (mipmapFilter == LINEAR) glFilter += 2;
   glTexParameteri(target, GL_TEXTURE_MIN_FILTER, glFilter);
}

void Texture::setMagFilter(Filter filter) const {
   glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::setMaxAnisotropy(int value) {
   if (value == 0) value = 1;
   if (value < 0 || value > getMaxAnisotropyMax()) value = getMaxAnisotropyMax();
   // GL_TEXTURE_MAX_ANISOTROPY_EXT = 0x84FE
   glTexParameterf(target, 0x84FE, value);
}

void Texture::unbind() const {
   glBindTexture(target, 0);
}
