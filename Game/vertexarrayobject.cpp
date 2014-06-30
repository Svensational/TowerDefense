#include "vertexarrayobject.h"
#include <utility>
#include "gl_core_4_4.h"

VertexArrayObject::VertexArrayObject() :
   name(0)
{
   glGenVertexArrays(1, &name);
}

VertexArrayObject::VertexArrayObject(VertexArrayObject && other) :
   name(other.name)
{
   other.name = 0;
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

VertexArrayObject & VertexArrayObject::operator =(VertexArrayObject && other) {
   std::swap(name, other.name);
   return *this;
}

void VertexArrayObject::unbind() {
   glBindVertexArray(0);
}

void VertexArrayObject::vertexAttributePointer(unsigned int index, int size, Type type, bool normalized, int stride, int offset) const {
   glVertexAttribPointer(index, size, type, normalized, stride, reinterpret_cast<void*>(offset));
}
