#include "shaderobject.h"
#include "gl_core_4_4.h"

ShaderObject::ShaderObject(Type type) :
   name(glCreateShader(type))
{
}

ShaderObject::~ShaderObject() {
   glDeleteShader(name);
}

void ShaderObject::compile() const {
   glCompileShader(name);
}
