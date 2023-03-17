#version 400
in vec3 normal_var;
out vec4 FragColor;
void main()
{
   float r = (normal_var[0]+1)/2.0;
   float g = (normal_var[1]+1)/2.0;
   float b = (normal_var[2]+1)/2.0;
   FragColor = vec4(r, g, b, 1.0);
}