#ifndef RENDERBUFFEROBJECT_H
#define RENDERBUFFEROBJECT_H

class RenderbufferObject {

public:
   RenderbufferObject();
   RenderbufferObject(RenderbufferObject && other);
   virtual ~RenderbufferObject();
   RenderbufferObject & operator =(RenderbufferObject && other);
   void bind() const;
   void unbind() const;

private:
   unsigned int name;
};

#endif // RENDERBUFFEROBJECT_H
