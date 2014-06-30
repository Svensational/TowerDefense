#ifndef INDEXBUFFEROBJECT_H
#define INDEXBUFFEROBJECT_H

#include "bufferobject.h"

template <typename T>
class IndexBufferObject : public BufferObject {

public:
   IndexBufferObject() :
      BufferObject()
   {
      switch (sizeof(T)) {
         case 1:
            type = UNSIGNED_BYTE;
            break;
         case 2:
            type = UNSIGNED_SHORT;
            break;
         default:
            type = UNSIGNED_INT;
            break;
      }
   }

   IndexBufferObject(IndexBufferObject && other) :
      BufferObject(other.name, other.target, other.count), type(other.type)
   {
      other.name = 0;
   }

   IndexBufferObject & operator =(IndexBufferObject && other) {
      std::swap(name, other.name);
      target = other.target;
      count = other.count;
      type = other.type;
      return *this;
   }

   void bind() {
      BufferObject::bind(ELEMENT_ARRAY_BUFFER);
   }

   void createStorage(Usage usage, int count, T const * data = nullptr) {
      BufferObject::createStorage(usage, count, sizeof(T), data);
   }

   T * map(Access access) const {
      return reinterpret_cast<T*>(BufferObject::map(access));
   }

   T * mapRange(int offset, int length, Access access) const {
      return reinterpret_cast<T*>(BufferObject::mapRange(offset, length, access));
   }

   void draw(Mode mode) const {
      BufferObject::drawElements(mode, type, count);
   }

   void draw(Mode mode, int count) const {
      BufferObject::drawElements(mode, type, count);
   }

private:
   IBOType type;
};

#endif // INDEXBUFFEROBJECT_H
