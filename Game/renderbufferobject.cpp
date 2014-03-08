#include "renderbufferobject.h"
#include <utility>
#include "gl_core_4_4.h"

RenderbufferObject::RenderbufferObject() :
   name(0)
{
   glGenRenderbuffers(1, &name);
}

RenderbufferObject::RenderbufferObject(RenderbufferObject && other) :
   name(other.name)
{
   other.name = 0;
}

RenderbufferObject::~RenderbufferObject() {
   glDeleteRenderbuffers(1, &name);
}

void RenderbufferObject::bind() const {
   glBindRenderbuffer(GL_RENDERBUFFER, name);
}

RenderbufferObject & RenderbufferObject::operator =(RenderbufferObject && other) {
   std::swap(name, other.name);
   return *this;
}

void RenderbufferObject::unbind() const {
   glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
