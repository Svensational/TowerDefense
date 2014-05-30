#version 330

in vec3 normal_camera;
in vec3 reflect_camera;
in vec3 eye_camera;
in vec2 texCoords;

uniform sampler2D textureSampler;
uniform vec3 lightColor;

out vec3 color;

void main() {
   vec3 n = normalize(normal_camera);
   vec3 r = normalize(reflect_camera);
   vec3 e = normalize(eye_camera);

   float ambient = 0.1;
   float diffuse = clamp(dot(n, r), 0, 1);
   float specular = pow(clamp(dot(e, r), 0, 1), 8);

   color = texture(textureSampler, texCoords).rgb * lightColor * (ambient + diffuse + specular);
}
