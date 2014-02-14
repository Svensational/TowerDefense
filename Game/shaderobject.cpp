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

void ShaderObject::setSourceCode(std::string const & filename) const {
   std::ifstream ifs(filename);

   std::string string((std::istreambuf_iterator<char>(ifs)),
                       std::istreambuf_iterator<char>());
   char const * cString = string.c_str();

   glShaderSource(name, 1, &cString, nullptr);
}
