#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "texture.h"
#include "image.h"

class Texture2D : public Texture {

public:
   Texture2D();
   Texture2D(Texture2D && other);
   Texture2D & operator =(Texture2D && other);

   bool createStorage(Size2i size, int levels = -1);
   void setImage(Image const & image, int level = 0) const;
   void setSubImage(int xOffset, int yOffset, Image const & image, int level = 0) const;
   void setWrapHeuristics(WrapHeuristic heuristic) const;
   void setWrapHeuristics(WrapHeuristic heuristicS, WrapHeuristic heuristicT) const;
   void generateMipmaps() const;

   bool isCreated() const;
   Size2i getSize(int level = 0) const;
   Image getImage(int level = 0) const;

private:
   bool created;
   Size2i size;
   int levels;
};

#endif // TEXTURE2D_H
