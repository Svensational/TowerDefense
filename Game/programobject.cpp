#include "programobject.h"
#include "gl_core_4_4.h"
#include "shaderobject.h"

ProgramObject::ProgramObject() :
   name(glCreateProgram())
{
}

ProgramObject::ProgramObject(ProgramObject && other) :
   name(other.name)
{
   other.name = 0;
}

ProgramObject::~ProgramObject() {
   glDeleteProgram(name);
}

void ProgramObject::attachShader(ShaderObject const & shader) const {
   glAttachShader(name, shader.name);
}

void ProgramObject::bindAttributeLocation(int index, std::string attribName) const {
   glBindAttribLocation(name, index, attribName.c_str());
}

void ProgramObject::detachShader(ShaderObject const & shader) const {
   glDetachShader(name, shader.name);
}

int ProgramObject::getAttributeLocation(std::string attribName) const {
   return glGetAttribLocation(name, attribName.c_str());
}

std::string ProgramObject::getLog() const {
   int infoLogLength;
   glGetProgramiv(name, GL_INFO_LOG_LENGTH, &infoLogLength);
   char logArray[infoLogLength];
   glGetProgramInfoLog(name, infoLogLength, nullptr, logArray);
   return std::string(logArray);
}

bool ProgramObject::link() const {
   glLinkProgram(name);
   int didLink;
   glGetProgramiv(name, GL_LINK_STATUS, &didLink);
   return didLink;
}

ProgramObject & ProgramObject::operator =(ProgramObject && other) {
   std::swap(name, other.name);
   return *this;
}

void ProgramObject::use() const {
   glUseProgram(name);
}
