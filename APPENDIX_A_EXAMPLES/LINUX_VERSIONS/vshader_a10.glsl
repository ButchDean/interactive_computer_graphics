
#version 150

in  vec4 vPosition;

uniform mat4 Projection;

void main() 
{
    gl_Position = Projection * vPosition;
} 
