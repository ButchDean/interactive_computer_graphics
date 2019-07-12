attribute  vec4 vPosition;
attribute  vec4 vTexCoord;
varying vec2 texCoord;

uniform mat4 Projection;

void main() 
{
    // We only need the s and t values of the texture coordinate
    texCoord = vTexCoord.st;
    gl_Position = Projection * vPosition;
} 
