#version 150

in  vec4 vPosition;
in  vec4 vColor;
in  vec2 vTexCoord;

out vec4 color;
out vec2 texCoord;

uniform vec3 theta;

void main() 
{
    const float  DegreesToRadians = 3.14159265 / 180.0;
    
    vec3 c = cos( DegreesToRadians * theta );
    vec3 s = sin( DegreesToRadians * theta );

    mat4 rx = mat4( 1.0, 0.0,  0.0, 0.0,
		    0.0, c.x, -s.x, 0.0,
		    0.0, s.x,  c.x, 0.0,
		    0.0, 0.0,  0.0, 1.0);

    mat4 ry = mat4(   c.y, 0.0, s.y, 0.0,
		      0.0, 1.0, 0.0, 0.0,
		     -s.y, 0.0, c.y, 0.0,
		      0.0, 0.0, 0.0, 1.0 );

    // Workaround for bug in ATI driver
    ry[1][0] = 0.0;
    ry[1][1] = 1.0;
    
    mat4 rz = mat4( c.z, -s.z, 0.0, 0.0,
		    s.z,  c.z, 0.0, 0.0,
		    0.0,  0.0, 1.0, 0.0,
		    0.0,  0.0, 0.0, 1.0 );

    // Workaround for bug in ATI driver
    rz[2][2] = 1.0;
    
    color       = vColor;
    texCoord    = vTexCoord;
    gl_Position = rz * ry * rx * vPosition;
} 
