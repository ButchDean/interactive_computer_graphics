
#version 150

in  vec4 vPosition;
in  vec4 vTexCoord;
out vec2 texCoord;

uniform mat4 Projection;

void main() 
{
    // We only need the s and t values of the texture coordinate
    texCoord = vTexCoord.st;
    gl_Position = Projection * vPosition;
} 
