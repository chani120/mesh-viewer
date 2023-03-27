#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTextureCoords;

struct light {
  vec4 pos;
  vec3 la;
  vec3 ld;
  vec3 ls;
  float exponent;  
  float cutoff;
};

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;
uniform light light_var;

out vec3 Pos;
out vec3 Norm;
out vec3 SpotDir;  

void main() {
  Pos = vec3(ModelViewMatrix * vec4(vPos, 1.0));
  Norm = normalize(NormalMatrix * vNormals);
  SpotDir = normalize(-(light_var.pos.xyz));
  gl_Position = MVP * vec4(vPos, 1.0);
}