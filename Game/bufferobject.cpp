#include "bufferobject.h"
#include <utility>
#include "gl_core_4_4.h"

BufferObject::BufferObject() :
   name(0), target(ARRAY_BUFFER), size(0)
{
   glGenBuffers(1, &name);
}

BufferObject::BufferObject(unsigned int name, Target target, int size) :
   name(name), target(target), size(size)
{
   // don't create buffer since this is only for the initialization of subclasses
}

BufferObject::BufferObject(BufferObject && other) :
   name(other.name), target(other.target), size(other.size)
{
   other.name = 0;
}

BufferObject::~BufferObject() {
   glDeleteBuffers(1, &name);
}

void BufferObject::bind(Target target) {
   this->target = target;
   glBindBuffer(target, name);
}

void BufferObject::createStorage(Usage usage, int size, void const * data) {
   this->size = size;

   glBufferData(target, size, data, usage);
}

void * BufferObject::map(Access access) const {
   return glMapBuffer(target, access);
}

void * BufferObject::mapRange(int offset, int length, Access access) const {
   int glAccess;
   switch (access) {
      case READ_ONLY:
         glAccess = GL_MAP_READ_BIT;
         break;
      case WRITE_ONLY:
         glAccess = GL_MAP_WRITE_BIT;
         break;
      default:
         glAccess = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT;
   }
   return glMapBufferRange(target, offset, length, glAccess);
}

BufferObject & BufferObject::operator=(BufferObject && other) {
   std::swap(name, other.name);
   target = other.target;
   size = other.size;
   return *this;
}

void BufferObject::unbind() const {
   glBindBuffer(target, 0);
}

void BufferObject::unmap() const {
   glUnmapBuffer(target);
}
