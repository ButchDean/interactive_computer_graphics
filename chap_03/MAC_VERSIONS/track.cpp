//
// Display a color cube
//
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projetion.

#include "Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

point4 points[NumVertices];
color4 colors[NumVertices];

int     winWidth, winHeight;

float   angle = 0.0,  trans[3];
vec3 axis;
bool    trackingMouse = false;
bool    redrawContinue = false;
bool    trackballMove = false;

GLuint rquat_loc;
vec4 rquat = vec4(1.0, 0.0, 0.0, 0.0);

int s;

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[8] = {
    point4( -0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5, -0.5, -0.5, 1.0 ),
    point4( -0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5, -0.5, -0.5, 1.0 )
};

// RGBA olors
color4 vertex_colors[8] = {
    color4( 0.0, 0.0, 0.0, 1.0 ),  // black
    color4( 1.0, 0.0, 0.0, 1.0 ),  // red
    color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    color4( 0.0, 1.0, 0.0, 1.0 ),  // green
    color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    color4( 1.0, 1.0, 1.0, 1.0 ),  // white
    color4( 0.0, 1.0, 1.0, 1.0 )   // cyan
};


//----------------------------------------------------------------------------

// quad generates two triangles for each face and assigns colors
//    to the vertices
int Index = 0;
void
quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
}

//----------------------------------------------------------------------------

// generate 12 triangles: 36 vertices and 36 colors
void
colorcube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

//----------------------------------------------------------------------------

// OpenGL initialization

void
init()
{
    colorcube();

    // Create a vertex array object
    GLuint vao;
    glGenVertexArraysAPPLE( 1, &vao );
    glBindVertexArrayAPPLE( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
		  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vtrack.glsl", "ftrack.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( program, "vColor" ); 
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(sizeof(points)) );

    rquat_loc = glGetUniformLocation( program, "rquat" );
    
    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}


// quaternion multiplier

vec4 multq(vec4 a, vec4 b)
{
   vec3 aa = vec3(a[1], a[2], a[3]);
   vec3 bb = vec3(b[1], b[2], b[3]);
   vec3 cc = a[0]*bb+b[0]*aa+cross(bb, aa);
   return(vec4(a[0]*b[0] - dot(aa, bb), cc[0], cc[1], cc[2]));
}


//----------------------------------------------------------------------

//  These functions implement a simple trackball-like motion control.

   vec3 lastPos = vec3(0.0, 0.0, 0.0);
   int curx, cury;
   int startX, startY;

vec3 
trackball_ptov(int x, int y, int width, int height)
{
    float d, a;
    vec3 v;

    // project x,y onto a hemi-sphere centered within width, height 

    v[0] = (2.0*x - width) / width;
    v[1] = (height - 2.0*y) / height;

// ensure that we are inside the circle on the z = 0 plane

    d = sqrt(v[0]*v[0] + v[1]*v[1]);
    if(d < 1.0) v[2] = cos((M_PI/2.0)*d);
      else v[2] = 0.0;

    a = 1.0 / sqrt(dot(v,v));
    v *= a;

    return v;
}


void
mouseMotion(int x, int y)
{
    vec3 curPos;
    vec3 d;

    curPos = trackball_ptov(x, y, winWidth, winHeight);
    if(trackingMouse)
    {
       d = curPos - lastPos;
       float a = dot(d,d);

//check if mouse moved

       if (a) 
       {
           // slow down rotation if needed by changed speed
           float speed = 1.1;

           angle = speed * (M_PI/2.0)*sqrt(a);

// compute and normalize rotatation direction vector

           axis = cross(lastPos, curPos);
           a = 1.0/sqrt(dot(axis, axis));

           lastPos = curPos;
        }
   }
    glutPostRedisplay();
}

void
startMotion(int x, int y)
{

    trackingMouse = true;
    redrawContinue = false;
    startX = x; startY = y;
    curx = x; cury = y;
    lastPos = trackball_ptov(x, y, winWidth, winHeight);
    trackballMove=true;
}

void
stopMotion(int x, int y)
{

    trackingMouse = false;

    if (startX != x || startY != y) {
        redrawContinue = true;
    } else {
        angle = 0.0F;
        redrawContinue = false;
        trackballMove = false;
    }
}

/*----------------------------------------------------------------------*/


void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

// form quaterion from angle and axis and increment present rotation quaterion

    if (trackballMove) 
        rquat = multq(vec4(cos(angle/2.0), sin(angle/2.0)*axis[0], sin(angle/2.0)*axis[1], sin(angle/2.0)*axis[2]), rquat);
    glUniform4fv( rquat_loc, 4, rquat );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );

    glutSwapBuffers();
}


void mouseButton(int button, int state, int x, int y)
{

// use right button to start mouse tracking when down and stop when up

        if(button==GLUT_RIGHT_BUTTON) exit(0);
        if(button==GLUT_LEFT_BUTTON) switch(state)
        {
    case GLUT_DOWN:
        y=winHeight-y;
        startMotion( x,y);
        break;
    case GLUT_UP:
        stopMotion( x,y);
        break;
    }
}

//----------------------------------------------------------------------------

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    winWidth = w;
    winHeight = h;
}

//----------------------------------------------------------------------------

void spinCube()
{
    if (redrawContinue) glutPostRedisplay();
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Color Cube" );

    init();

    glutDisplayFunc( display );
    glutReshapeFunc(myReshape);
    glutMouseFunc( mouseButton );
    glutIdleFunc( spinCube );
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
