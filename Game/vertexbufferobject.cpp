#include "vertexbufferobject.h"
#include <utility>
#include "gl_core_4_4.h"

VertexBufferObject::VertexBufferObject() :
   BufferObject()
{
}

VertexBufferObject::VertexBufferObject(VertexBufferObject && other) :
   BufferObject(other.name, other.target, other.size)
{
   other.name = 0;
}

void VertexBufferObject::bind() {
   BufferObject::bind(ARRAY_BUFFER);
}

void VertexBufferObject::draw(Mode mode, unsigned int vertexsize) const {
   glDrawArrays(mode, 0, size/vertexsize);
}

VertexBufferObject & VertexBufferObject::operator =(VertexBufferObject && other) {
   std::swap(name, other.name);
   target = other.target;
   size = other.size;
   return *this;
}
