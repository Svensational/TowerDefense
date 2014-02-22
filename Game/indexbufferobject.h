#ifndef INDEXBUFFEROBJECT_H
#define INDEXBUFFEROBJECT_H

#include "bufferobject.h"

template <typename T>
class IndexBufferObject : public BufferObject {

public:
   IndexBufferObject() :
      BufferObject()
   {
   }

   IndexBufferObject(IndexBufferObject && other) :
      BufferObject(other.name, other.target, other.count)
   {
      other.name = 0;
   }

   IndexBufferObject & operator =(IndexBufferObject && other) {
      std::swap(name, other.name);
      target = other.target;
      count = other.count;
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
      BufferObject::drawElements(mode, sizeof(T));
   }
};

template <typename T>
using IBO = IndexBufferObject<T>;

using IBOub = IndexBufferObject<unsigned char>;
using IBOus = IndexBufferObject<unsigned short>;
using IBOui = IndexBufferObject<unsigned int>;

#endif // INDEXBUFFEROBJECT_H
