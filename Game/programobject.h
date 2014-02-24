#ifndef PROGRAMOBJECT_H
#define PROGRAMOBJECT_H
#include <string>

class ShaderObject;
class Mat4f;

class ProgramObject {

public:
   ProgramObject();
   ProgramObject(ProgramObject && other);
   virtual ~ProgramObject();
   ProgramObject & operator =(ProgramObject && other);
   void attachShader(ShaderObject const & shader) const;
   void detachShader(ShaderObject const & shader) const;
   bool link() const;
   void use() const;

   void bindAttributeLocation(int index, std::string attribName) const;
   int getAttributeLocation(std::string attribName) const;
   int getUniformLocation(std::string uniformName) const;
   std::string getLog() const;

   void setUniform(std::string uniformName, float v0) const;
   void setUniform(std::string uniformName, Mat4f const & mat) const;
   static void setUniform(int location, float v0);
   static void setUniform(int location, Mat4f const & mat);

private:
   unsigned int name;
};

#endif // PROGRAMOBJECT_H
