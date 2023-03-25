#version 400

in vec3 position_var;
in vec3 normal_var;
out vec4 FragColor;

struct light{
   vec4 pos;
   vec3 la;
   vec3 ld;
   vec3 ls;
};
uniform light light_var;

struct material{
   vec3 ka;
   vec3 kd;
   vec3 ks;
   float shine;
};
uniform material mat_var;

const int level = 3;
const float scale = 1.0 / level;

vec3 toon(){
   vec3 s = normalize(vec3(light_var.pos.xyz) - position_var);
   float cos = max(0.0, dot(s, normal_var));
   vec3 dif = ((mat_var.kd + mat_var.ks + mat_var.ka)) * ceil(cos * level) * scale;
   return light_var.la * (mat_var.ka + dif);
}

void main(){
   FragColor = vec4(toon(), 1.0);
}