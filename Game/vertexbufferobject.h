#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include "bufferobject.h"

class VertexBufferObject : public BufferObject {

public:
   VertexBufferObject();
   VertexBufferObject(VertexBufferObject && other);
   VertexBufferObject & operator =(VertexBufferObject && other);
   void bind();
   void draw(Mode mode, unsigned int vertexsize) const;
};

typedef VertexBufferObject VBO;

#endif // VERTEXBUFFEROBJECT_H
