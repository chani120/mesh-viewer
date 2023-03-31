#version 400
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

out vec3 color;
out vec2 vUv;
out vec3 norm;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main(){
	norm = vNormal;
	vUv = vTexCoord;
	color = vec3(1.0, 1.0, 1.0);
	gl_Position = MVP * vec4(vPosition, 1.0);
}