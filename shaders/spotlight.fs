#version 400

struct light {
  vec4 pos;  
  vec3 la;
  vec3 ld;
  vec3 ls;
  float exponent;  
  float cutoff;
};

struct material {
  float shine;
  vec3 ka;
  vec3 kd;
  vec3 ks;
};

uniform light light_var1;
uniform material mat_var;

in vec3 Pos;
in vec3 Norm;
in vec3 SpotDir; 
out vec4 FragColor;

vec3 spotlightShade() {
  vec3 s = normalize(vec3(light_var1.pos.xyz) - Pos);
  float angle = acos(dot(-s, SpotDir));
  float cutoff = radians(clamp(light_var1.cutoff, 0.0, 90.0));
  vec3 ambient = light_var1.la * mat_var.ka;

  if (angle < cutoff) {
    float spotFactor = pow(dot(-s, SpotDir), light_var1.exponent);
    vec3 v = normalize(vec3(-Pos));
    vec3 h = normalize(v + s);
    return ambient + (spotFactor * light_var1.la * (mat_var.kd * max(dot(s, Norm), 0.0)) + (mat_var.ks * pow(max(dot(h, Norm), 0.0), mat_var.shine)));
  } 
  else{
    return ambient;
  }
}

void main() {
  FragColor = vec4(spotlightShade(), 1.0);
}