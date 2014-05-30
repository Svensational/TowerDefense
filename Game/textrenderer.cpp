#include "textrenderer.h"
#include "gl_core_4_4.h"
#include "vertex.h"
#include "programobject.h"
#include "font.h"
#include "text.h"
#include "resourcemanager.h"

TextRenderer::TextRenderer() :
   program(ResourceManager::getGlobalInstance()->getProgram("text")),
   textColorLocation(0), mvpLocation(0)
{
   init();
}

TextRenderer::~TextRenderer() {
}

void TextRenderer::addText(Text * text) {
   texts.insert(std::pair<std::string, Text*>(text->fontname, text));
}

void TextRenderer::init() {
   if (program) {
      program->use();
      program->setUniform("textTexture", 0);
      textColorLocation = program->getUniformLocation("textColor");
      mvpLocation = program->getUniformLocation("mvp");
   }
}

void TextRenderer::render(Mat4f const & vpMat) const {
   if (!program) return;
   glEnable(GL_PRIMITIVE_RESTART);
   glPrimitiveRestartIndex(65535);
   program->use();

   Font * font;

   for (unsigned int i=0; i<texts.bucket_count(); ++i) {
      if (texts.bucket_size(i)) {
         font = ResourceManager::getGlobalInstance()->getFont(texts.begin(i)->first);
         if (font) {
            font->bindToTIU(0);
         }
         else {
            break;
         }
         for (auto local_it=texts.begin(i); local_it!=texts.end(i); ++local_it) {
            program->setUniform(textColorLocation, Vec3f(1.0f, 0.5f, 0.5f));
            program->setUniform(mvpLocation, vpMat*local_it->second->modelMat);
            local_it->second->render();
         }
      }
   }

   glDisable(GL_PRIMITIVE_RESTART);
}
