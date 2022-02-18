#version 150

in  vec4 vPosition;
out vec4 color;

void
main()
{
    gl_Position = vPosition;
    color =
        vec4( ( 1.0 + vPosition.x ) / 2.0, ( 1.0 + vPosition.y ) / 2.0,
              ( 1.0 + vPosition.z ) / 2.0, 1.0 );
}
