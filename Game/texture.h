#ifndef TEXTURE_H
#define TEXTURE_H

class FramebufferObject;

class Texture {
   friend class FramebufferObject;

public:
   enum Target {
      TEXTURE_1D                   = 0x0DE0, // 1.1
      TEXTURE_2D                   = 0x0DE1, // 1.1
      TEXTURE_3D                   = 0x806F, // 1.2
      TEXTURE_RECTANGLE            = 0x84F5, // 3.1
      TEXTURE_CUBE_MAP             = 0x8513, // 1.3
      TEXTURE_1D_ARRAY             = 0x8C18, // 3.0
      TEXTURE_2D_ARRAY             = 0x8C1A, // 3.0
      TEXTURE_BUFFER               = 0x8C2A, // 3.1
      TEXTURE_CUBE_MAP_ARRAY       = 0x9009, // 4.0
      TEXTURE_2D_MULTISAMPLE       = 0x9100, // 3.2
      TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9102  // 3.2
   };

   enum Filter {
      NEAREST = 0x2600,
      LINEAR  = 0x2601
   };

   enum WrapHeuristic {
      REPEAT          = 0x2901,
      CLAMP_TO_BORDER = 0x812D,
      CLAMP_TO_EDGE   = 0x812F,
      MIRRORED_REPEAT = 0x8370
   };

   virtual ~Texture();
   void bind() const;
   void bindToTIU(unsigned short textureImageUnit) const;
   void unbind() const;

   void setMinFilter(Filter filter) const;
   void setMinFilter(Filter filter, Filter mipmapFilter) const;
   void setMagFilter(Filter filter) const;
   void setMaxAnisotropy(int value = -1);
   void setBorderColor(float r, float g, float b, float a) const;

   static void setActiveTextureImageUnit(unsigned short unit);
   static int getMaxTextureImageUnits();
   static int getMaxAnisotropyMax();

protected:
   unsigned int name;
   Target target;

   explicit Texture(Target target);
   Texture(unsigned int name, Target target);

private:
   static int getMaxTextureImageUnitsPriv();
   static int getMaxAnisotropyMaxPriv();
};

#endif // TEXTURE_H
