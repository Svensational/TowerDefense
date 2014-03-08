#ifndef RENDERBUFFEROBJECT_H
#define RENDERBUFFEROBJECT_H

struct Size2i;

class RenderbufferObject {

public:
   enum Format {
      COLOR         = 0x8058, //GL_RGBA8
      DEPTH         = 0x81A6, //GL_DEPTH_COMPONENT24
      DEPTH_STENCIL = 0x88F0  //GL_DEPTH24_STENCIL8
   };

   RenderbufferObject();
   RenderbufferObject(RenderbufferObject && other);
   virtual ~RenderbufferObject();
   RenderbufferObject & operator =(RenderbufferObject && other);
   void bind() const;
   void unbind() const;
   void createStorage(Size2i const & size, Format format = DEPTH_STENCIL, int samples = 0) const;

private:
   unsigned int name;
};

#endif // RENDERBUFFEROBJECT_H
