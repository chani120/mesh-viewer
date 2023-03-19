#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

out vec3 normal_var;
out vec4 position_var;

void main(){
	normal_var = normalize(NormalMatrix * vNormals);
	position_var = ModelViewMatrix * vec4(vPos, 1.0);
    gl_Position = MVP * vec4(vPos, 1.0);
}