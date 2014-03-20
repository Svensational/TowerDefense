#ifndef FRAMEBUFFEROBJECT_H
#define FRAMEBUFFEROBJECT_H
#include <string>
#include "size2i.h"

class Texture2D;
class RenderbufferObject;

class FramebufferObject {

public:
   enum Target {
      READ      = 0x8CA8,
      DRAW      = 0x8CA9,
      READ_DRAW = 0x90D2
   };

   FramebufferObject();
   FramebufferObject(FramebufferObject && other);
   virtual ~FramebufferObject();
   FramebufferObject & operator =(FramebufferObject && other);
   void bind(Target target);
   void unbind() const;

   void attach(Texture2D const & texture, unsigned short pointIndex = 0, unsigned short level = 0);
   void attach(RenderbufferObject const & renderbufferObject, unsigned short pointIndex = 0);

   void setViewport(Size2i const & size) const;
   void setViewport(Rect2i const & rect) const;
   void clear(bool colorBuffer = true, bool depthbuffer = false, bool stencilBuffer = false);
   std::string getStatusString() const;

private:
   unsigned int name;
   Target currentTarget;
};

using FBO = FramebufferObject;

#endif // FRAMEBUFFEROBJECT_H
