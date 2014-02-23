#version 330
in vec2 texCoords;
out vec3 color;
uniform sampler2D textureSampler;

void main() {
   //color = vec3(1.0, 0.0, 0.0);
   color = texture(textureSampler, texCoords).rgb;
}
