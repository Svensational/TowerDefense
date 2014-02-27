#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
//layout(location = 2) in vec4 vertexColor;
layout(location = 3) in vec2 vertexTexCoords;

uniform vec3 lightDir;
uniform mat4 mv;
uniform mat4 v;
uniform mat4 mvp;

out vec3 lightDir_camera;
out vec3 normal_camera;
out vec3 eyeDir_camera;
out vec2 texCoords;

void main() {
   gl_Position = mvp * vec4(vertexPosition, 1.0);

   lightDir_camera = (v * vec4(lightDir, 0.0)).xyz;
   normal_camera = (mv * vec4(vertexNormal, 0.0)).xyz;
   eyeDir_camera =  -(mv * vec4(vertexPosition, 1.0)).xyz;

   texCoords = vertexTexCoords;
}
