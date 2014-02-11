#include "vertexbufferobject.h"
#include "gl_core_4_4.h"

VertexBufferObject::VertexBufferObject() :
   BufferObject()
{
}

void VertexBufferObject::bind() {
   BufferObject::bind(ARRAY_BUFFER);
}

void VertexBufferObject::draw(Mode mode, unsigned int vertexsize) const {
   glDrawArrays(mode, 0, size/vertexsize);
}
