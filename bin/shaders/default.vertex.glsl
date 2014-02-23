#version 330

layout(location = 0) in vec3 vertexPosition;
//layout(location = 1) in vec3 vertexNormal;
//layout(location = 2) in vec4 vertexColor;
layout(location = 3) in vec2 vertexTexCoords;
out vec2 texCoords;

void main() {
   gl_Position = vec4(vertexPosition, 1.0);
   texCoords = vertexTexCoords;
}
