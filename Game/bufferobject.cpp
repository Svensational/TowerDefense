#include "bufferobject.h"
#include <utility>
#include "gl_core_4_4.h"

BufferObject::BufferObject() :
   name(0), target(ARRAY_BUFFER), count(0)
{
   glGenBuffers(1, &name);
}

BufferObject::BufferObject(unsigned int name, Target target, int count) :
   name(name), target(target), count(count)
{
   // don't create buffer since this is only for the initialization of subclasses
}

BufferObject::BufferObject(BufferObject && other) :
   name(other.name), target(other.target), count(other.count)
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

void BufferObject::createStorage(Usage usage, int count, int entrySize, void const * data) {
   this->count = count;

   glBufferData(target, count*entrySize, data, usage);
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
   count = other.count;
   return *this;
}

void BufferObject::unmap() const {
   glUnmapBuffer(target);
}
