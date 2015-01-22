#version 150

in  vec4 vPosition;
in  vec3 vColor;
out vec4 color;

void
main()
{
    gl_Position = vPosition;
    color = vec4( vColor, 1.0 );
}
