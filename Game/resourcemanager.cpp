#include "resourcemanager.h"
#include "font.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager() {
   deleteFonts();
}

void ResourceManager::deleteFonts() {
   for (auto & font : fonts) {
      delete font.second;
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
