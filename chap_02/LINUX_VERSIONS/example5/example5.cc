/* Generate contours using marching cubes */

#include "Angel.h"

const GLfloat Xmin = -1.0;
const GLfloat Xmax = 1.0;
const GLfloat Ymin = -1.0;
const GLfloat Ymax = 1.0;

const int NumXCells = 50;
const int NumYCells = 50;

const GLfloat Threshold = 0.0;

const int NumPoints = 10000;
vec2 points[NumPoints];

GLuint ProjLoc;

int Count = 0;

//----------------------------------------------------------------------------

GLfloat
f( GLfloat x, GLfloat y )
{
    GLfloat a = 0.49;
    GLfloat b = 0.50;

    // Elliptical equation for ovals of Cassini

    GLfloat s = x * x + y * y + a * a;
    GLfloat t = 4 * a * a * x * x + b * b * b * b;

    return s * s - t;
}

//----------------------------------------------------------------------------

int
cell( GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
    int n = 0;

    if ( a > Threshold ) n += 1;
    if ( b > Threshold ) n += 8;
    if ( c > Threshold ) n += 4;
    if ( d > Threshold ) n += 2;

    return n;
}

//----------------------------------------------------------------------------

void
draw_one( int num, int i, int j, GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
    const GLfloat dx = ( Xmax - Xmin ) / (NumXCells - 1);
    const GLfloat dy = ( Ymax - Ymin ) / (NumYCells - 1);

    GLfloat ox = Xmin + i * dx;
    GLfloat oy = Ymin + j * dy;

    GLfloat x1, x2, y1, y2;

    switch ( num ) {
    case 1:
    case 14:
        x1 = ox;
        y1 = oy + dy * ( Threshold - a ) / ( d - a );
        x2 = ox + dx * ( Threshold - a ) / ( b - a );
        y2 = oy;
        break;
    case 2:
    case 13:
        x1 = ox;
        y1 = oy + dy * ( Threshold - a ) / ( d - a );
        x2 = ox + dx * ( Threshold - d ) / ( c - d );
        y2 = oy + dy;
        break;
    case 4:
    case 11:
        x1 = ox + dx * ( Threshold - d ) / ( c - d );
        y1 = oy + dy;
        x2 = ox + dx;
        y2 = oy + dy * ( Threshold - b ) / ( c - b );
        break;
    case 7:
    case 8:
        x1 = ox + dx * ( Threshold - a ) / ( b - a );
        y1 = oy;
        x2 = ox + dx;
        y2 = oy + dy * ( Threshold - b ) / ( c - b );
        break;
    }

    points[Count++] = vec2( x1, y1 );
    points[Count++] = vec2( x2, y2 );
}

//----------------------------------------------------------------------------

void
draw_adjacent( int num, int i, int j, GLfloat a, GLfloat b, GLfloat c,
               GLfloat d )
{
    const GLfloat dx = ( Xmax - Xmin ) / (NumXCells - 1);
    const GLfloat dy = ( Ymax - Ymin ) / (NumYCells - 1);

    GLfloat ox = Xmin + i * dx;
    GLfloat oy = Ymin + j * dy;

    GLfloat x1, x2, y1, y2;

    switch ( num ) {
    case 3:
    case 12:
        x1 = ox + dx * ( Threshold - a ) / ( b - a );
        y1 = oy;
        x2 = ox + dx * ( Threshold - d ) / ( c - d );
        y2 = oy + dy;
        break;
    case 6:
    case 9:
        x1 = ox;
        y1 = oy + dy * ( Threshold - a ) / ( d - a );
        x2 = ox + dx;
        y2 = oy + dy * ( Threshold - b ) / ( c - b );
        break;
    }

    points[Count++] = vec2( x1, y1 );
    points[Count++] = vec2( x2, y2 );
}

//----------------------------------------------------------------------------

void
draw_opposite( int num, int i, int j,
               GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
    const GLfloat dx = ( Xmax - Xmin ) / (NumXCells - 1);
    const GLfloat dy = ( Ymax - Ymin ) / (NumYCells - 1);

    GLfloat ox = Xmin + i * dx;
    GLfloat oy = Ymin + j * dy;

    GLfloat x1, x2, x3, x4, y1, y2, y3, y4;

    switch ( num ) {
    case 5:
        x1 = ox;
        y1 = oy + dy * ( Threshold - a ) / ( d - a );
        x2 = ox + dx * ( Threshold - a ) / ( b - a );
        y2 = oy;
        x3 = ox + dx * ( Threshold - d ) / ( c - d );
        y3 = oy + dy;
        x4 = ox + dx;
        y4 = oy + dy * ( Threshold - b ) / ( c - b );
        break;
    case 10:
        x1 = ox;
        y1 = oy + dy * ( Threshold - a ) / ( d - a );
        x2 = ox + dx * ( Threshold - d ) / ( c - d );
        y2 = oy + dy;
        x3 = ox + dy * ( Threshold - a ) / ( b - a );
        y3 = oy;
        x4 = ox + dx;
        y4 = oy + dy * ( Threshold - b ) / ( c - b );
        break;

    }

    points[Count++] = vec2( x1, y1 );
    points[Count++] = vec2( x2, y2 );
    points[Count++] = vec2( x3, y3 );
    points[Count++] = vec2( x4, y4 );
}

//----------------------------------------------------------------------------

void
lines( int num, int i, int j, GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
    switch ( num ) {
    case 1:
    case 2:
    case 4:
    case 7:
    case 8:
    case 11:
    case 13:
    case 14:
        draw_one( num, i, j, a, b, c, d );
        break;
    case 3:
    case 6:
    case 9:
    case 12:
        draw_adjacent( num, i, j, a, b, c, d );
        break;
    case 5:
    case 10:
        draw_opposite( num, i, j, a, b, c, d );
        break;
    case 0:
    case 15:
        break;
    }
}

//----------------------------------------------------------------------------

void
init( void )
{
    // Generate an array of data from the function f(x,y)
    GLfloat data[NumXCells][NumYCells];

    const GLfloat dx = ( Xmax - Xmin ) / (NumXCells - 1);
    const GLfloat dy = ( Ymax - Ymin ) / (NumYCells - 1);

    for ( int i = 0; i < NumXCells; ++i ) {
        GLfloat x = Xmin + i * dx;

        for ( int j = 0; j < NumYCells; ++j ) {
            GLfloat y = Ymin + j * dy;

            data[i][j] = f( x, y );
        }
    }

    // Compute contours for each data cell
    for ( int i = 0; i < NumXCells; ++i ) {
        for ( int j = 0; j < NumYCells; ++j ) {
            int c = cell( data[i][j], data[i+1][j],
                          data[i+1][j+1], data[i][j+1] );

            lines( c, i, j, data[i][j], data[i+1][j],
                   data[i+1][j+1], data[i][j+1] );
        }
    }

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader25.glsl", "fshader25.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    ProjLoc = glGetUniformLocation( program, "Proj" );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    glDrawArrays( GL_LINES, 0, Count );
    glFlush();
}

//----------------------------------------------------------------------------

void
reshape( int w, int h )
{
    glViewport( 0, 0, w, h );

    GLfloat xmin = Xmin, xmax = Xmax, ymin = Ymin, ymax = Ymax;
    GLfloat aspect = GLfloat(w) / h;

    if ( aspect < 1.0 ) {
        ymin /= aspect;
        ymax /= aspect;
    }
    else {
        xmin *= aspect;
        xmax *= aspect;
    }

    mat4 ortho = Ortho2D( xmin, xmax, ymin, ymax );
    glUniformMatrix4fv( ProjLoc, 1, GL_FALSE, ortho );
}

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
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 3, 1 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Simple GLSL example" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
