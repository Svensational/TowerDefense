#version 330

in vec3 lightDir_camera;
in vec3 normal_camera;
in vec3 eyeDir_camera;
in vec2 texCoords;

uniform sampler2D textureSampler;
uniform vec3 lightColor;

out vec3 color;

void main() {
   vec3 l = normalize(lightDir_camera);
   vec3 n = normalize(normal_camera);
   vec3 r = reflect(l, n);
   vec3 e = normalize(eyeDir_camera);
   float cosTheta = clamp(dot(n, l), 0, 1);
   float cosAlpha = clamp(dot(e, r), 0, 1);

   color = texture(textureSampler, texCoords).rgb * lightColor * (0.1 + cosTheta + pow(cosAlpha, 5));
}
