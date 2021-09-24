
#include "Angel.h"

const int NumVertices = 500;

void
init()
{
    // Generate spline data
    vec2  points[NumVertices];
    
    for ( int i = 0; i < NumVertices; ++i ) {
	// Spline control points
	const vec2 p[4] = {
	    vec2( -1.00, -1.00 ),
	    vec2( -0.33,  1.00 ),
	    vec2(  0.33,  1.00 ),
	    vec2(  1.00, -1.00 )
	};

	const float d = 1.0 / ( NumVertices - 1.0 );

        float u = i * d;
        float v = 1.0 - u;
	
	points[i] =
	    (u*u*u)*p[0] + 3*(u*u*v)*p[1] + 3*(u*v*v)*p[2] + (v*v*v)*p[3];
//             points[i][j] =
//                 p[0][j] * uu * uu * uu + 3.0 * p[1][j] * uu * uu * u +
//                 3.0 * p[2][j] * uu * u * u + p[3][j] * u * u * u;
    }

    // Create a vertex array object
    GLuint vao;
    glGenVertexArraysAPPLE( 1, &vao );
    glBindVertexArrayAPPLE( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader102.glsl", "fshader102.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 2, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    glDrawArrays( GL_LINE_STRIP, 0, NumVertices );
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033:  // Escape key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
    }
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Simple GLSL example" );

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    
    glutMainLoop();
    return 0;
}
