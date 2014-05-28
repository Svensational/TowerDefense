#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <unordered_map>

class Font;

class ResourceManager {

public:
   ResourceManager();
   virtual ~ResourceManager();

   Font * const getFont(std::string const & name);

   static ResourceManager * getGlobalInstance();

private:
   std::unordered_map<std::string, Font*> fonts;

   void deleteFonts();
};

#endif // RESOURCEMANAGER_H
