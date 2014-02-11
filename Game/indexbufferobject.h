#ifndef INDEXBUFFEROBJECT_H
#define INDEXBUFFEROBJECT_H

#include "bufferobject.h"

class IndexBufferObject : public BufferObject {

public:
   enum Type {
      UNSIGNED_BYTE  = 0x1401,
      UNSIGNED_SHORT = 0x1403,
      UNSIGNED_INT   = 0x1405
   };

   IndexBufferObject();
   void bind();
   void draw(Mode mode, Type type) const;

};

typedef IndexBufferObject IBO;

#endif // INDEXBUFFEROBJECT_H
