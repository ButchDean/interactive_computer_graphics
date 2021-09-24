#version 150

in vec4 vPosition;
out vec4 color;

void
main()
{
    color = vec4( 0.5 + vPosition.x, 0.5 + vPosition.y,	
		  0.5 + vPosition.z, 1.0 );
    gl_Position = vPosition;
}
