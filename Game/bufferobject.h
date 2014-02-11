#ifndef BUFFEROBJECT_H
#define BUFFEROBJECT_H

class BufferObject {

public:
   enum Target {
      ARRAY_BUFFER              = 0x8892,
      ELEMENT_ARRAY_BUFFER      = 0x8893,
      PIXEL_PACK_BUFFER         = 0x88EB,
      PIXEL_UNPACK_BUFFER       = 0x88EC,
      UNIFORM_BUFFER            = 0x8A11,
      TEXTURE_BUFFER            = 0x8C2A,
      TRANSFORM_FEEDBACK_BUFFER = 0x8C8E,
      DRAW_INDIRECT_BUFFER      = 0x8F3F,
      ATOMIC_COUNTER_BUFFER     = 0x92C0,
      DISPATCH_INDIRECT_BUFFER  = 0x90EE,
      SHADER_STORAGE_BUFFER     = 0x90D2
   };

   enum Access {
      READ_ONLY  = 0x88B8,
      WRITE_ONLY = 0x88B9,
      READ_WRITE = 0x88BA
   };

   enum Usage {
      STREAM_DRAW  = 0x88E0,
      STREAM_READ  = 0x88E1,
      STREAM_COPY  = 0x88E2,
      STATIC_DRAW  = 0x88E4,
      STATIC_READ  = 0x88E5,
      STATIC_COPY  = 0x88E6,
      DYNAMIC_DRAW = 0x88E8,
      DYNAMIC_READ = 0x88E9,
      DYNAMIC_COPY = 0x88EA
   };

   enum Mode {
      // OpenGL 1.1
      POINTS                   = 0x0000,
      LINES                    = 0x0001,
      LINE_LOOP                = 0x0002,
      LINE_STRIP               = 0x0003,
      TRIANGLES                = 0x0004,
      TRIANGLE_STRIP           = 0x0005,
      TRIANGLE_FAN             = 0x0006,
      // OpenGL 3.2
      LINES_ADJACENCY          = 0x000A,
      LINE_STRIP_ADJACENCY     = 0x000B,
      TRIANGLES_ADJACENCY      = 0x000C,
      TRIANGLE_STRIP_ADJACENCY = 0x000D,
      // OpenGL 4.0
      PATCHES                  = 0x000E
   };

   BufferObject();
   virtual ~BufferObject();
   void bind(Target target);
   void unbind() const;
   void createStorage(Usage usage, int size, void const * data = nullptr);
   void * map(Access access) const;
   void * mapRange(int offset, int length, Access access) const;
   void unmap() const;

protected:
   unsigned int name;
   Target target;
   int size;
};

#endif // BUFFEROBJECT_H
