#version 330

in vec2 texCoords;

uniform sampler2D textTexture;
uniform vec3 textColor;

out vec4 color;

void main() {
   float alpha = texture(textTexture, texCoords).r;
   if (alpha < 0.01) {
      discard;
   }
   color = vec4(textColor, alpha);
}
