#include "vertexarrayobject.h"
#include "gl_core_4_4.h"

VertexArrayObject::VertexArrayObject() {
   glGenVertexArrays(1, &name);
}

VertexArrayObject::~VertexArrayObject() {
   glDeleteVertexArrays(1, &name);
}

void VertexArrayObject::bind() const {
   glBindVertexArray(name);
}

void VertexArrayObject::unbind() {
   glBindVertexArray(0);
}
