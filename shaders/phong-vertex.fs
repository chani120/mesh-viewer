#version 400

in vec3 phong_result;
out vec4 FragColor;
void main(){
   FragColor = vec4(phong_result, 1.0);
}