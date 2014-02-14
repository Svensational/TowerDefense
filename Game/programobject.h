#ifndef PROGRAMOBJECT_H
#define PROGRAMOBJECT_H
#include <string>

class ShaderObject;

class ProgramObject {

public:
   ProgramObject();
   virtual ~ProgramObject();
   void attachShader(ShaderObject const & shader) const;
   void detachShader(ShaderObject const & shader) const;
   void bindAttributeLocation(int index, std::string attribName) const;
   int getAttributeLocation(std::string attribName) const;
   bool link() const;
   void use() const;
   std::string getLog() const;

private:
   unsigned int name;
};

#endif // PROGRAMOBJECT_H
