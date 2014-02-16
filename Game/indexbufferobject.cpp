#include "indexbufferobject.h"
#include <utility>
#include "gl_core_4_4.h"

IndexBufferObject::IndexBufferObject() :
   BufferObject()
{
}

IndexBufferObject::IndexBufferObject(IndexBufferObject && other) :
   BufferObject(other.name, other.target, other.size)
{
   other.name = 0;
}

void IndexBufferObject::bind() {
   BufferObject::bind(ELEMENT_ARRAY_BUFFER);
}

void IndexBufferObject::draw(Mode mode, Type type) const {
   int count;
   switch (type) {
      case UNSIGNED_BYTE:
         count = size;
         break;
      case UNSIGNED_SHORT:
         count = size/2;
         break;
      default:
         count = size/4;
         break;
   }
   glDrawElements(mode, count, type, 0);
}

IndexBufferObject & IndexBufferObject::operator =(IndexBufferObject && other) {
   std::swap(name, other.name);
   target = other.target;
   size = other.size;
   return *this;
}
