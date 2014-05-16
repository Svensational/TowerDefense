#include "textrenderer.h"
#include "gl_core_4_4.h"
#include "vertex.h"
#include "shaderobject.h"
#include "programobject.h"
#include "font.h"
#include "text.h"

TextRenderer::TextRenderer() :
   program(nullptr), textColorLocation(0), mvpLocation(0)
{
   init();
}

TextRenderer::~TextRenderer() {
   delete program;
}

void TextRenderer::addText(Text * text) {
   texts.insert(std::pair<std::string, Text *>("FONTNAME", text));
}

void TextRenderer::init() {
   // init program
   ShaderObject vertexShader(ShaderObject::VERTEX_SHADER);
   vertexShader.loadSource("shaders/text.vertex.glsl");
   vertexShader.compile();

   ShaderObject fragmentShader(ShaderObject::FRAGMENT_SHADER);
   fragmentShader.loadSource("shaders/text.fragment.glsl");
   fragmentShader.compile();

   program = new ProgramObject();
   program->attachShader(vertexShader);
   program->attachShader(fragmentShader);
   program->link();
   program->detachShader(vertexShader);
   program->detachShader(fragmentShader);

   program->use();
   program->setUniform("textTexture", 0);
   textColorLocation = program->getUniformLocation("textColor");
   mvpLocation = program->getUniformLocation("mvp");
}

void TextRenderer::render(Mat4f const & vpMat) const {
   glEnable(GL_PRIMITIVE_RESTART);
   glPrimitiveRestartIndex(65535);
   program->use();


   for (unsigned int i=0; i<texts.bucket_count(); ++i) {
      if (texts.bucket_size(i)) {
         /// @todo font should be moved to a global ressource manager
         texts.begin(i)->second->font->bindToTIU(0);
         for (auto local_it=texts.begin(i); local_it!=texts.end(i); ++local_it) {
            program->setUniform(textColorLocation, Vec3f(1.0f, 0.5f, 0.5f));
            program->setUniform(mvpLocation, vpMat*local_it->second->modelMat);
            local_it->second->render();
         }
      }
   }

   glDisable(GL_PRIMITIVE_RESTART);
}
