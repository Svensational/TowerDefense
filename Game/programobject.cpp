#include "programobject.h"
#include "gl_core_4_4.h"
#include "shaderobject.h"

ProgramObject::ProgramObject() :
   name(glCreateProgram())
{
}

ProgramObject::~ProgramObject() {
   glDeleteProgram(name);
}

void ProgramObject::attachShader(ShaderObject const & shader) {
   glAttachShader(name, shader.name);
}

void ProgramObject::bindAttributeLocation(int index, std::string attribName) {
   glBindAttribLocation(name, index, attribName.c_str());
}

void ProgramObject::detachShader(ShaderObject const & shader) {
   glDetachShader(name, shader.name);
}

int ProgramObject::getAttributeLocation(std::string attribName) {
   return glGetAttribLocation(name, attribName.c_str());
}

void ProgramObject::link() {
   glLinkProgram(name);
}
