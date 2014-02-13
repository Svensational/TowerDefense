#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

class VertexArrayObject {

public:
   VertexArrayObject();
   virtual ~VertexArrayObject();
   void bind() const;
   static void unbind();
   void enableVertexAttributeArray(unsigned int index) const;
   void disableVertexAttributeArray(unsigned int index) const;
   void vertexAttributePointer(unsigned int index, int size, int type, bool normalized, int stride, int offset);

private:
   unsigned int name;
};

typedef VertexArrayObject VAO;

#endif // VERTEXARRAYOBJECT_H
