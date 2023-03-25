#version 400

struct light {
  vec4 pos;  // spotlight location in eye coordinates
  vec3 La;
  vec3 Ld;
  vec3 Ls;
  float exponent;  // speed of decrease in brightness within spotlight
  // angle between center axis and edge of spotlight cone
  // in degrees in range [0, 90]
  float cutoff;
};

struct material {
  float shine;
  vec3 Ka;
  vec3 Kd;
  vec3 Ks;
};

uniform light light_var;
uniform material mat_var;

in vec3 position_var;
in vec3 normal_var;
in vec3 SpotDir;  // direction of spotlight (center axis) in eye coords
out vec4 FragColor;

vec3 spotlightShade() {
  // normalized direction to light_var source
  vec3 s = normalize(vec3(light_var.pos) - position_var);
  // angle between center of spotlight and light_var-to-pos vector
  float angle = acos(dot(-s, SpotDir));
  // clamp cutoff angle to 90 deg and convert to rads
  float cutoff = radians(clamp(light_var.cutoff, 0.0, 90.0));
  // compute ambient light_var
  vec3 ambient = light_var.La * mat_var.Ka;
  if (angle < cutoff) {
    // within spotlight, calculate brightness based on distance to core
    float spotFactor = pow(dot(-s, SpotDir), light_var.exponent);
    vec3 v = normalize(vec3(-position_var));
    vec3 h = normalize(v + s);
    return ambient + (spotFactor * light_var.La *
                (mat_var.Kd * max(dot(s, normal_var), 0.0)) + 
                (mat_var.Ks * pow(max(dot(h, normal_var), 0.0), mat_var.shine)));
  } else {
    return ambient;
  }
}

void main() {
  FragColor = vec4(spotlightShade(), 1.0);
}