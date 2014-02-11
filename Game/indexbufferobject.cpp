#include "indexbufferobject.h"
#include "gl_core_4_4.h"

IndexBufferObject::IndexBufferObject() :
   BufferObject()
{
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
