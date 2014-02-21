#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include "bufferobject.h"
#include "gl_core_4_4.h"

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
      this->count = count;
      glBufferData(target, count*sizeof(T), data, usage);
   }

   T * map(Access access) const {
      return reinterpret_cast<T*>(BufferObject::map(access));
   }

   T * mapRange(int offset, int length, Access access) const {
      return reinterpret_cast<T*>(BufferObject::mapRange(offset, length, access));
   }

   void draw(Mode mode) const {
      glDrawArrays(mode, 0, count);
   }
};

template <typename T>
using VBO = VertexBufferObject<T>;

#endif // VERTEXBUFFEROBJECT_H
