#version 150

in vec4 vPosition;
uniform mat4 model_view;
uniform mat4 projection;
void main() 
{
   gl_Position = projection*model_view*vPosition/vPosition.w;
} 
