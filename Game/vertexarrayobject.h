#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

class VertexArrayObject {

public:
   enum Type {
      BYTE                         = 0x1400,
      UNSIGNED_BYTE                = 0x1401,
      SHORT                        = 0x1402,
      UNSIGNED_SHORT               = 0x1403,
      INT                          = 0x1404,
      UNSIGNED_INT                 = 0x1405,
      FLOAT                        = 0x1406,
      DOUBLE                       = 0x140A,
      HALF_FLOAT                   = 0x140B,
      FIXED                        = 0x140C,
      UNSIGNED_INT_2_10_10_10_REV  = 0x8368,
      UNSIGNED_INT_10F_11F_11F_REV = 0x8C3B,
      INT_2_10_10_10_REV           = 0x8D9F
   };

   VertexArrayObject();
   VertexArrayObject(VertexArrayObject && other);
   virtual ~VertexArrayObject();
   VertexArrayObject & operator =(VertexArrayObject && other);
   void bind() const;
   static void unbind();
   void enableVertexAttributeArray(unsigned int index) const;
   void disableVertexAttributeArray(unsigned int index) const;
   void vertexAttributePointer(unsigned int index, int size, Type type, bool normalized, int stride, int offset) const;

private:
   unsigned int name;
};

using VAO = VertexArrayObject;

#endif // VERTEXARRAYOBJECT_H
