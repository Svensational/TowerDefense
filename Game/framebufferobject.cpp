#include "framebufferobject.h"
#include <utility>
#include "gl_core_4_4.h"

FramebufferObject::FramebufferObject() :
   name(0), currentTarget(READ_DRAW)
{
   glGenFramebuffers(1, &name);
}

FramebufferObject::FramebufferObject(FramebufferObject && other) :
   name(other.name), currentTarget(other.currentTarget)
{
   other.name = 0;
}

FramebufferObject::~FramebufferObject() {
   glDeleteFramebuffers(1, &name);
}

void FramebufferObject::bind(Target target) {
   currentTarget = target;
   glBindFramebuffer(currentTarget, name);
}

FramebufferObject & FramebufferObject::operator =(FramebufferObject && other) {
   std::swap(name, other.name);
   currentTarget = other.currentTarget;
   return *this;
}

void FramebufferObject::unbind() const {
   glBindFramebuffer(currentTarget, 0);
}
