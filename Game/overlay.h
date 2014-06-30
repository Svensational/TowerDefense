#ifndef OVERLAY_H
#define OVERLAY_H
#include "mat4f.h"

class Text;
class TextRenderer;

class Overlay
{
public:
   Overlay();
   virtual ~Overlay();
   void render() const;

private:
   Mat4f projectionMat;
   TextRenderer * textRenderer;
};

#endif // OVERLAY_H
