#include "Overlay.h"
#include "text.h"
#include "textrenderer.h"

Overlay::Overlay() :
   projectionMat(Mat4f::ortho(0.0f, 1.0f, 0.0f, 1.0f)),
   textRenderer(new TextRenderer())
{
   textRenderer->addText(new Text(Mat4f(), "text", U"test"));
}

Overlay::~Overlay()
{
   delete textRenderer;
}

void Overlay::render() const {
   textRenderer->render(projectionMat);
}
