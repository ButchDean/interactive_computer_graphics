//
// Display a Mandelbrot set
//

// Uncomment the following line to use user-specified input values
// #define USER_INPUT

#ifdef USER_INPUT
// Include the C++ iostreams classes for use when collecting user input
#include <iostream>
#endif 

#include "Angel.h"

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

// Use the C++ standard complex-number class.  It's a C++ template, so
//   we create a typedef of simplify our code.
#include <complex>
typedef std::complex<float>  Complex;

inline float Random() { return float(rand())/RAND_MAX; }

GLuint Projection;

/* default data*/
/* can enter other values via command line arguments */

#define CENTERX -0.5
#define CENTERY 0.5
#define HEIGHT 0.5
#define WIDTH 0.5
#define MAX_ITER 100

/* N x M array to be generated */

#define N 512
#define M 512

float height = HEIGHT;          /* size of window in complex plane */
float width = WIDTH;
float cx = CENTERX;             /* center of window in complex plane */
float cy = CENTERY;
int max = MAX_ITER;             /* number of interations per point */

int n = N;
int m = M;

GLfloat image[N][M][3];

//----------------------------------------------------------------------------

void
init( void )
{
#ifdef USER_INPUT
    // Collect user input to initialize program parameters
    cout << "Enter the center X coordinate: ";
    cin >> cx;
    cout << "Enter the center Y coordinate: ";
    cin >> cy;
    cout << "Enter the window's width: ";
    cin >> width;
    cout << "Enter the maximum number of iterations: ";
    cin >> max;
#endif

    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j < M; j++ ) {

            float x = i * ( width / (n - 1) ) + cx - width / 2;
            float y = j * ( height / ( m - 1 ) ) + cy - height / 2;

	    Complex c( 0.0, 0.0 );
	    Complex p( x, y );

	    float  v;
            for ( int k = 0; k < max; k++ ) {
		// compute c = c^2 + p
		c *= c;
		c += p;
		v = norm( c );
                if ( v > 4.0 )
                    break;      /* assume not in set if mag > 4 */
            }


            // assign gray level to point based on its magnitude */

            if ( v > 1.0 )
                v = 1.0;        /* clamp if > 1 */
            image[i][j][0] = v;
            image[i][j][1] = Random();
            image[i][j][1] = 2.0 * sin( v ) - 1.0;
            image[i][j][2] = 1.0 - v;
        }

    glActiveTexture( GL_TEXTURE0 );
    GLuint  texture;
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_FLOAT, image );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

    // Create a vertex array object
    GLuint vao;
    glGenVertexArraysAPPLE( 1, &vao );
    glBindVertexArrayAPPLE( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    point4 points[6] = {
	point4( 0.0, 0.0, 0.0, 1.0 ),
	point4( 0.0, 1.0, 0.0, 1.0 ),
	point4( 1.0, 1.0, 0.0, 1.0 ),
	point4( 1.0, 1.0, 0.0, 1.0 ),
	point4( 1.0, 0.0, 0.0, 1.0 ),
	point4( 0.0, 0.0, 0.0, 1.0 )
    };

    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader92.glsl", "fshader92.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    // Since our texture coordinates match our vertex positions, we
    //   can reuse the position data for our texture coordinates.
    GLuint vTexCoord = glGetAttribLocation( program, "vTexCoord" ); 
    glEnableVertexAttribArray( vTexCoord );
    glVertexAttribPointer( vTexCoord, 4, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    Projection = glGetUniformLocation( program, "Projection" );

    // Set our texture samples to the active texture unit
    glUniform1i( glGetUniformLocation(program, "texture"), 0 );

    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
    mat4 projection = Ortho( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );

}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033: // Escape Key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
    }
}

//----------------------------------------------------------------------------

void
display()
{
    glClear( GL_COLOR_BUFFER_BIT );
    glDrawArrays( GL_TRIANGLES, 0, 6 );
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

int
main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( N, M );
    glutCreateWindow( "mandlebrot" );

    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
