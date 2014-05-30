#include "resourcemanager.h"
#include "font.h"
#include "shaderobject.h"
#include "programobject.h"
#include "image.h"
#include "texture2d.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager() {
   deleteFonts();
   deletePrograms();
   deleteTextures();
}

void ResourceManager::deleteFonts() {
   for (auto & element : fonts) {
      delete element.second;
   }
}

void ResourceManager::deletePrograms() {
   for (auto & element : programs) {
      delete element.second;
   }
}

void ResourceManager::deleteTextures() {
   for (auto & element : textures) {
      delete element.second;
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
      vertexShader.loadSource("shaders/"+name+".vert.glsl");
      vertexShader.compile();

      ShaderObject fragmentShader(ShaderObject::FRAGMENT_SHADER);
      fragmentShader.loadSource("shaders/"+name+".frag.glsl");
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

Texture2D * const ResourceManager::getTexture(std::string const & name) {
   if (textures.count(name) == 0) {
      Image image;
      image.loadPNG("images/"+name+".png");
      Texture2D * texture = nullptr;
      if (!image.isNull()) {
         texture = new Texture2D();
         texture->bind();
         texture->createStorage(image.getSize());
         texture->setImage(image);
         texture->generateMipmaps();
         texture->setMinFilter(Texture::LINEAR, Texture::LINEAR);
         texture->setMagFilter(Texture::LINEAR);
         texture->setMaxAnisotropy();
         if (!texture->isCreated()) {
            delete texture;
            texture = nullptr;
         }
      }
      textures.insert(std::pair<std::string, Texture2D*>(name, texture));
   }
   return textures[name];
}




