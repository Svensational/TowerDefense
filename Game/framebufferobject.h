#ifndef FRAMEBUFFEROBJECT_H
#define FRAMEBUFFEROBJECT_H
#include <string>

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
   std::string getStatusString() const;

private:
   unsigned int name;
   Target currentTarget;
};

using FBO = FramebufferObject;

#endif // FRAMEBUFFEROBJECT_H
