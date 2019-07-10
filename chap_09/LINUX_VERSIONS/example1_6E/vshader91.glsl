
#version 150

in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;

void main() 
{
    gl_Position = Projection * ModelView * vPosition;
    color = vColor;
} 
