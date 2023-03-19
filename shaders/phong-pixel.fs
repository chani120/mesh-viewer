#version 400

in vec4 position_var;
in vec3 normal_var;

out vec4 FragColor;
vec3 phong(vec4 p, vec3 n, vec3 a, vec3 d, vec3 sp, vec3 c){
	vec4 pos = vec4(5, 10, 0, 1);
	vec4 light_vec = normalize(pos - p);

	vec3 s = normalize(vec3(light_vec - p));
	vec3 v = normalize(-vec3(p));
	vec3 r = reflect(-s,n);

	vec3 amb = c * a;
	vec3 diff = c * d * max(dot(s,n),0.0);
	vec3 spec = vec3(0.0);
	if(dot(s,n) > 0.0){
		spec = c * sp * pow(max(dot(r,v),0.0), 0.3);
	}

	vec3 light = amb + diff + spec;
	return light;
}

void main(){
	vec3 ambient = vec3(0.25,0.3,0.6);
	vec3 diffuse = vec3(0.2,0.2,0.1);
	vec3 specular = vec3(0.6,0.25,0.1);
	vec3 color = vec3(0.4,0.8,0.9);
	FragColor = vec4(phong(position_var, normal_var, ambient, diffuse, specular, color), 1.0);
}