#include "resourcemanager.h"
#include "font.h"
#include "shaderobject.h"
#include "programobject.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager() {
   deleteFonts();
   deletePrograms();
}

void ResourceManager::deleteFonts() {
   for (auto & font : fonts) {
      delete font.second;
   }
}

void ResourceManager::deletePrograms() {
   for (auto & program : programs) {
      delete program.second;
   }
}

ResourceManager * ResourceManager::getGlobalInstance() {
   static ResourceManager * globalResources = new ResourceManager();
   return globalResources;
}

Font * const ResourceManager::getFont(std::string const & name) {
   if (fonts.count(name) == 0) {
      Font * font = new Font("fonts/"+name+".ttf");
      if (font->isNull()) {
         delete font;
         font = nullptr;
      }
      fonts.insert(std::pair<std::string, Font*>(name, font));
   }
   return fonts[name];
}

ProgramObject * const ResourceManager::getProgram(std::string const & name) {
   if (programs.count(name) == 0) {
      ShaderObject vertexShader(ShaderObject::VERTEX_SHADER);
      vertexShader.loadSource("shaders/"+name+".vertex.glsl");
      vertexShader.compile();

      ShaderObject fragmentShader(ShaderObject::FRAGMENT_SHADER);
      fragmentShader.loadSource("shaders/"+name+".fragment.glsl");
      fragmentShader.compile();

      ProgramObject * program = new ProgramObject();
      program->attachShader(vertexShader);
      program->attachShader(fragmentShader);
      bool didLink = program->link();
      program->detachShader(vertexShader);
      program->detachShader(fragmentShader);
      if (!didLink) {
         delete program;
         program = nullptr;
      }
      programs.insert(std::pair<std::string, ProgramObject*>(name, program));
   }
   return programs[name];
}
