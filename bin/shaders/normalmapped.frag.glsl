#version 330

in vec3 normal_camera;
in vec3 tangent_camera;
in vec3 reflect_camera;
in vec3 eye_camera;
in vec2 texCoords;

uniform sampler2D textureSampler;
uniform sampler2D normalMapSampler;
uniform vec3 lightColor;

out vec4 color;

vec3 calcBumpedNormal() {
   vec3 normal = normalize(normal_camera);
   vec3 tangent = normalize(tangent_camera - dot(tangent_camera, normal) * normal);
   vec3 bitangent = cross(tangent, normal);

   vec3 normalMapNormal = 2.0 * texture(normalMapSampler, texCoords).rgb - vec3(1.0, 1.0, 1.0);

   return normalize(mat3(tangent, bitangent, normal) * normalMapNormal);
}

void main() {
   vec3 n = calcBumpedNormal();
   vec3 r = normalize(reflect_camera);
   vec3 e = normalize(eye_camera);

   float ambient = 0.1;
   float diffuse = clamp(dot(n, r), 0, 1);
   float specular = pow(clamp(dot(e, r), 0, 1), 8);

   color = vec4(texture(textureSampler, texCoords).rgb * lightColor * (ambient + diffuse + specular), 1.0);
}
