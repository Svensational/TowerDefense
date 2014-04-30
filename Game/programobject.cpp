#include "programobject.h"
#include "gl_core_4_4.h"
#include "mat4f.h"
#include "vec.h"
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

int ProgramObject::getUniformLocation(std::string uniformName) const {
   return glGetUniformLocation(name, uniformName.c_str());
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

void ProgramObject::setUniform(int location, int val) {
   glUniform1i(location, val);
}

void ProgramObject::setUniform(std::string uniformName, int val) const {
   glUniform1i(getUniformLocation(uniformName), val);
}

void ProgramObject::setUniform(int location, float val) {
   glUniform1f(location, val);
}

void ProgramObject::setUniform(std::string uniformName, float val) const {
   glUniform1f(getUniformLocation(uniformName), val);
}

void ProgramObject::setUniform(int location, Vec3f const & vec) {
   glUniform3fv(location, 1, vec);
}

void ProgramObject::setUniform(std::string uniformName, Vec3f const & vec) const {
   glUniform3fv(getUniformLocation(uniformName), 1, vec);
}

void ProgramObject::setUniform(int location, Mat4f const & mat) {
   glUniformMatrix4fv(location, 1, false, mat);
}

void ProgramObject::setUniform(std::string uniformName, Mat4f const & mat) const {
   glUniformMatrix4fv(getUniformLocation(uniformName), 1, false, mat);
}

void ProgramObject::use() const {
   glUseProgram(name);
}
