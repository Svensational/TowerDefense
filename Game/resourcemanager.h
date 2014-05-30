#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <unordered_map>

class Font;
class ProgramObject;

class ResourceManager {

public:
   ResourceManager();
   virtual ~ResourceManager();

   Font * const getFont(std::string const & name);
   ProgramObject * const getProgram(std::string const & name);

   static ResourceManager * getGlobalInstance();

private:
   std::unordered_map<std::string, Font*> fonts;
   std::unordered_map<std::string, ProgramObject*> programs;

   void deleteFonts();
   void deletePrograms();
};

#endif // RESOURCEMANAGER_H
