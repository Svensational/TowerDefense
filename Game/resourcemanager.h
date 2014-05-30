#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <unordered_map>

class Font;
class ProgramObject;
class Texture2D;

class ResourceManager {

public:
   ResourceManager();
   virtual ~ResourceManager();

   Font * const getFont(std::string const & name);
   ProgramObject * const getProgram(std::string const & name);
   Texture2D * const getTexture(std::string const & name);

   static ResourceManager * getGlobalInstance();

private:
   std::unordered_map<std::string, Font*> fonts;
   std::unordered_map<std::string, ProgramObject*> programs;
   std::unordered_map<std::string, Texture2D*> textures;

   void deleteFonts();
   void deletePrograms();
   void deleteTextures();
};

#endif // RESOURCEMANAGER_H
