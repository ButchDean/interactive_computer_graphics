attribute  vec3 vPosition;
attribute  vec3 vColor;
varying vec4 color;

void
main()
{
    gl_Position = vec4(vPosition, 1.0);
    color = vec4( vColor, 1.0 );
}
