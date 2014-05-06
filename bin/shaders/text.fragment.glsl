#version 330

in vec2 texCoords;

uniform sampler2D textTexture;
uniform vec3 textColor;

out vec3 color;

void main() {
   float alpha = texture(textTexture, texCoords).a;
   if (alpha < 0.01) {
      discard;
   }
   color = alpha * textColor;
}
