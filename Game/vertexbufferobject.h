#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include "bufferobject.h"

template <typename T>
class VertexBufferObject : public BufferObject {

public:
   VertexBufferObject() :
      BufferObject()
   {
   }

   VertexBufferObject(VertexBufferObject && other) :
      BufferObject(other.name, other.target, other.count)
   {
      other.name = 0;
   }

   VertexBufferObject & operator =(VertexBufferObject && other) {
      std::swap(name, other.name);
      target = other.target;
      count = other.count;
      return *this;
   }

   void bind() {
      BufferObject::bind(ARRAY_BUFFER);
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
      BufferObject::drawArrays(mode);
   }

   size_t elementSize() const {
      return sizeof(T);
   }
};

template <typename T>
using VBO = VertexBufferObject<T>;

#endif // VERTEXBUFFEROBJECT_H
