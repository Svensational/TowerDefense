#include "bufferobject.h"
#include "gl_core_4_4.h"

BufferObject::BufferObject() {
   glGenBuffers(1, &name);
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

void BufferObject::unbind() const {
   glBindBuffer(target, 0);
}

void BufferObject::unmap() const {
   glUnmapBuffer(target);
}
