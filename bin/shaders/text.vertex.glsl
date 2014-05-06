#version 330

layout(location = 0) in vec2 vertexPosition;
layout(location = 3) in vec2 vertexTexCoords;

uniform mat4 mvp;

out vec2 texCoords;

void main() {
   gl_Position = mvp * vec4(vertexPosition, 0.0, 1.0);

   texCoords = vertexTexCoords;
}
