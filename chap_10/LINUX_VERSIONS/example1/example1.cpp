
#include "Angel.h"

typedef Angel::vec4 point4;

// Define a convenient type for referencing patch control points, which
//   is used in the declaration of the vertices' array (used in "vertices.h")
typedef GLfloat     point3[3];
#include "vertices.h"
#include "patches.h"

const int NumTimesToSubdivide = 3;
const int PatchesPerSubdivision = 4;
const int NumQuadsPerPatch = 64;
// const int NumQuadsPerPatch = (int) pow( PatchesPerSubdivision, NumTimesToSubdivide );
const int NumTriangles = 32*64*2;
// const int NumTriangles = ( NumTeapotPatches * NumQuadsPerPatch * 2 /* triangles / quad */ );
const int NumVertices = 32*64*2*3;
//     ( NumTriangles * 3 /* vertices / triangle */ );

int     Index = 0;
point4  points[NumVertices];

GLuint  Projection;

enum { X = 0, Y = 1, Z = 2 };

//----------------------------------------------------------------------------

void
divide_curve( point4 c[4], point4 r[4], point4 l[4] )
{
    // Subdivide a Bezier curve into two equaivalent Bezier curves:
    //   left (l) and right (r) sharing the midpoint of the middle
    //   control point
    point4  t, mid = ( c[1] + c[2] ) / 2;

    l[0] = c[0];
    l[1] = ( c[0] + c[1] ) / 2;
    l[2] = ( l[1] + mid ) / 2;

    r[3] = c[3];
    r[2] = ( c[2] + c[3] ) / 2;
    r[1] = ( mid + r[2] ) / 2;

    l[3] = r[0] = ( l[2] + r[1] ) / 2;
    
    for ( int i = 0; i < 4; ++i ) {
	l[i].w = 1.0;
	r[i].w = 1.0;
    }
}

//----------------------------------------------------------------------------

void
draw_patch( point4 p[4][4] )
{
    // Draw the quad (as two triangles) bounded by the corners of the
    //   Bezier patch.
    points[Index++] = p[0][0];
    points[Index++] = p[3][0];
    points[Index++] = p[3][3];
    points[Index++] = p[0][0];
    points[Index++] = p[3][3];
    points[Index++] = p[0][3];
}

//----------------------------------------------------------------------------

inline void
transpose( point4 a[4][4] )
{
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = i; j < 4; j++ ) {
	    point4 t = a[i][j];
	    a[i][j] = a[j][i];
	    a[j][i] = t;
	}
    }
}

void
divide_patch( point4 p[4][4], int count )
{
    if ( count > 0 ) {
	point4 q[4][4], r[4][4], s[4][4], t[4][4];
	point4 a[4][4], b[4][4];

	// subdivide curves in u direction, transpose results, divide
	// in u direction again (equivalent to subdivision in v)
        for ( int k = 0; k < 4; ++k ) {
            divide_curve( p[k], a[k], b[k] );
	}

        transpose( a );
        transpose( b );

        for ( int k = 0; k < 4; ++k ) {
            divide_curve( a[k], q[k], r[k] );
            divide_curve( b[k], s[k], t[k] );
        }

	// recursive division of 4 resulting patches
        divide_patch( q, count - 1 );
        divide_patch( r, count - 1 );
        divide_patch( s, count - 1 );
        divide_patch( t, count - 1 );
    }
    else {
        draw_patch( p );
    }
}

//----------------------------------------------------------------------------

void
init( void )
{
    for ( int n = 0; n < NumTeapotPatches; n++ ) {
	point4  patch[4][4];

	// Initialize each patch's control point data
	for ( int i = 0; i < 4; ++i ) {
	    for ( int j = 0; j < 4; ++j ) {
		point3& v = vertices[indices[n][i][j]];
		patch[i][j] = point4( v[X], v[Y], v[Z], 1.0 );
	    }
	}

	// Subdivide the patch
        divide_patch( patch, NumTimesToSubdivide );
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
    GLuint program = InitShader( "vshader101.glsl", "fshader101.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    Projection = glGetUniformLocation( program, "Projection" );

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );

    GLfloat  left = -4.0, right = 4.0;
    GLfloat  bottom = -3.0, top = 5.0;
    GLfloat  zNear = -10.0, zFar = 10.0;

    GLfloat  aspect = GLfloat(width)/height;

    if ( aspect > 0 ) {
	left *= aspect;
	right *= aspect;
    }
    else {
	bottom /= aspect;
	top /= aspect;
    }

    mat4 projection = Ortho( left, right, bottom, top, zNear, zFar );
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
	case 'q': case 'Q': case 033 /* Escape key */:
	    exit( EXIT_SUCCESS );
	    break;
    }
}

//----------------------------------------------------------------------------

int
main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "teapot" );

    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
