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

void VertexArrayObject::disableVertexAttributeArray(unsigned int index) const {
   glDisableVertexAttribArray(index);
}

void VertexArrayObject::enableVertexAttributeArray(unsigned int index) const {
   glEnableVertexAttribArray(index);
}

void VertexArrayObject::unbind() {
   glBindVertexArray(0);
}

void VertexArrayObject::vertexAttributePointer(unsigned int index, int size, int type, bool normalized, int stride, int offset) {
   glVertexAttribPointer(index, size, type, normalized, stride, reinterpret_cast<void*>(offset));
}
