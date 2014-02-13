#ifndef PROGRAMOBJECT_H
#define PROGRAMOBJECT_H
#include <string>

class ShaderObject;

class ProgramObject {

public:
   ProgramObject();
   virtual ~ProgramObject();
   void attachShader(ShaderObject const & shader);
   void detachShader(ShaderObject const & shader);
   void bindAttributeLocation(int index, std::string attribName);
   int getAttributeLocation(std::string attribName);
   void link();

private:
   unsigned int name;
};

#endif // PROGRAMOBJECT_H
