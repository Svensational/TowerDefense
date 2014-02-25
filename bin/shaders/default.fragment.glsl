#version 330

in vec2 texCoords;
out vec3 color;
uniform sampler2D textureSampler;

void main() {
   color = texture(textureSampler, texCoords).rgb;
}
