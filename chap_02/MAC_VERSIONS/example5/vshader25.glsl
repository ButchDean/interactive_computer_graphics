#version 150 

uniform mat4  Proj;

in vec4 vPosition;

void
main()
{
    gl_Position = Proj * vPosition;
}
