#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H
#include <string>

class ProgramObject;

class ShaderObject {

   friend class ProgramObject;

public:
   enum Type {
      FRAGMENT_SHADER        = 0x8B30,
      VERTEX_SHADER          = 0x8B31,
      GEOMETRY_SHADER        = 0x8DD9,
      // OpenGL 4.0
      TESS_EVALUATION_SHADER = 0x8E87,
      TESS_CONTROL_SHADER    = 0x8E88,
      // OpenGL 4.3
      COMPUTE_SHADER         = 0x91B9
   };

   explicit ShaderObject(Type type);
   ShaderObject(ShaderObject && other);
   virtual ~ShaderObject();
   ShaderObject & operator =(ShaderObject && other);
   void setSource(std::string const & source) const;
   bool loadSource(std::string const & filename) const;
   bool compile() const;
   std::string getLog() const;

private:
   unsigned int name;
};

#endif // SHADEROBJECT_H
