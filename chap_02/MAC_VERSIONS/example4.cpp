/* sierpinski gasket with vertex arrays */

#include "Angel.h"

const int NumTimesToSubdivide = 4;
const int NumTetrahedrons = 256;            // 4^5 tetrahedrons
const int NumTriangles = 4*NumTetrahedrons;  // 4 triangles / tetrahedron
const int NumVertices = 3*NumTriangles;      // 3 vertices / triangle

vec3 points[NumVertices];
vec3 colors[NumVertices];

int  Index = 0;

//----------------------------------------------------------------------------

void
triangle( const vec3& a, const vec3& b, const vec3& c, const int color )
{
    static vec3  base_colors[] = {
	vec3( 1.0, 0.0, 0.0 ),
	vec3( 0.0, 1.0, 0.0 ),
	vec3( 0.0, 0.0, 1.0 ),
	vec3( 0.0, 0.0, 0.0 )
    };
    points[Index] = a;  colors[Index] = base_colors[color];  Index++;
    points[Index] = b;  colors[Index] = base_colors[color];  Index++;
    points[Index] = c;  colors[Index] = base_colors[color];  Index++;
}

//----------------------------------------------------------------------------

void
tetra( const vec3& a, const vec3& b, const vec3& c, const vec3& d )
{
    triangle( a, b, c, 0 );
    triangle( a, c, d, 1 );
    triangle( a, d, b, 2 );
    triangle( b, d, c, 3 );
}

//----------------------------------------------------------------------------

void
divide_tetra( const vec3& a, const vec3& b,
	      const vec3& c, const vec3& d, int count )
{
    if ( count > 0 ) {
        vec3 v0 = ( a + b ) / 2.0;
        vec3 v1 = ( a + c ) / 2.0;
        vec3 v2 = ( a + d ) / 2.0;
	vec3 v3 = ( b + c ) / 2.0;
	vec3 v4 = ( c + d ) / 2.0;
	vec3 v5 = ( b + d ) / 2.0;
        divide_tetra( a, v0, v1, v2, count - 1 );
        divide_tetra( v0, b, v3, v5, count - 1 );
        divide_tetra( v1, v3, c, v4, count - 1 );
	divide_tetra( v2, v5, v4, d, count - 1 );
    }
    else {
        tetra( a, b, c, d );    // draw tetrahedron at end of recursion
    }
}

//----------------------------------------------------------------------------

void
init( void )
{
    vec3 vertices[4] = {
	vec3( 0.0, 0.0, -1.0 ),
	vec3( 0.0, 0.942809, 0.333333 ),
	vec3( -0.816497, -0.471405, 0.333333 ),
	vec3( 0.816497, -0.471405, 0.333333 )
    };	

    // Subdivide the original tetrahedron
    divide_tetra( vertices[0], vertices[1], vertices[2], vertices[3],
		  NumTimesToSubdivide );

    // Create a vertex array object
    GLuint vao;
    glGenVertexArraysAPPLE( 1, &vao );
    glBindVertexArrayAPPLE( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // First, we create an empty buffer of the size we need by passing
    //   a NULL pointer for the data values
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
		  NULL, GL_STATIC_DRAW );

    // Next, we load the real data in parts.  We need to specify the
    //   correct byte offset for placing the color data after the point
    //   data in the buffer.  Conveniently, the byte offset we need is
    //   the same as the size (in bytes) of the points array, which is
    //   returned from "sizeof(points)".
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader24.glsl", "fshader24.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader    
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    // Likewise, initialize the vertex color attribute.  Once again, we
    //    need to specify the starting offset (in bytes) for the color
    //    data.  Just like loading the array, we use "sizeof(points)"
    //    to determine the correct value.
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );

    glEnable( GL_DEPTH_TEST );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); /* white background */
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    glFlush(); }

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Simple GLSL example" );

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
