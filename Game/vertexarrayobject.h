#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

class VertexArrayObject {

public:
   VertexArrayObject();
   virtual ~VertexArrayObject();
   void bind() const;
   static void unbind();

private:
   unsigned int name;
};

typedef VertexArrayObject VAO;

#endif // VERTEXARRAYOBJECT_H
