#include "shaderobject.h"
#include <fstream>
#include "gl_core_4_4.h"

ShaderObject::ShaderObject(Type type) :
   name(glCreateShader(type))
{
}

ShaderObject::~ShaderObject() {
   glDeleteShader(name);
}

bool ShaderObject::compile() const {
   glCompileShader(name);
   int didCompile;
   glGetShaderiv(name, GL_COMPILE_STATUS, &didCompile);
   return didCompile;
}

std::string ShaderObject::getLog() const {
   int infoLogLength;
   glGetShaderiv(name, GL_INFO_LOG_LENGTH, &infoLogLength);
   char logArray[infoLogLength];
   glGetShaderInfoLog(name, infoLogLength, nullptr, logArray);
   return std::string(logArray);
}

bool ShaderObject::loadSource(std::string const & filename) const {
   std::ifstream ifs(filename);

   if (ifs.is_open()) {
      setSource(std::string((std::istreambuf_iterator<char>(ifs)),
                             std::istreambuf_iterator<char>()));
      return true;
   }
   else {
      return false;
   }
}

void ShaderObject::setSource(std::string const & source) const {
   char const * cString = source.c_str();
   glShaderSource(name, 1, &cString, nullptr);
}
