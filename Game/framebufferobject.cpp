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

std::string FramebufferObject::getStatusString() const {
   switch (glCheckFramebufferStatus(currentTarget)) {
   case GL_FRAMEBUFFER_COMPLETE:
      return std::string("The FBO is complete and can be used.");
   case GL_FRAMEBUFFER_UNDEFINED:
      return std::string("No FBO is bound and the default framebuffer does not exist.");
   case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      return std::string("One or more attachments are incomplete.");
   case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      return std::string("There are no images attached to the FBO.");
   case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
      return std::string("One or more draw buffers specify an attachment point that has no image attached and is not GL_NONE.");
   case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
      return std::string("The read buffer specifies an attachment point that has no image attached.");
   case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
      return std::string("Not all images have the same number of multisample samples.");
   case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
      return std::string("Layered and unlayered attachements are mixed.");
   default:
      return std::string("Unknown status.");
   }
}

FramebufferObject & FramebufferObject::operator =(FramebufferObject && other) {
   std::swap(name, other.name);
   currentTarget = other.currentTarget;
   return *this;
}

void FramebufferObject::unbind() const {
   glBindFramebuffer(currentTarget, 0);
}