/* Particles in a box */

#define MAX_NUM_PARTICLES 1000
#define INITIAL_NUM_PARTICLES 25
#define INITIAL_POINT_SIZE 5.0
#define INITIAL_SPEED 1.0
#define NUM_COLORS 8
#define FALSE 0
#define TRUE 1

#include "Angel.h"

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

point4 vertices[8] = {
    point4( -1.1, -1.1,  1.1, 1.0 ),
    point4( -1.1,  1.1,  1.1, 1.0 ),
    point4(  1.1,  1.1,  1.1, 1.0 ),
    point4(  1.1, -1.1,  1.1, 1.0 ),
    point4( -1.1, -1.1, -1.1, 1.0 ),
    point4( -1.1,  1.1, -1.1, 1.0 ),
    point4(  1.1,  1.1, -1.1, 1.0 ),
    point4(  1.1, -1.1, -1.1, 1.0 )
};

// RGBA colors
color4 vertex_colors[8] = {
    color4( 0.0, 0.0, 0.0, 1.0 ),       // black
    color4( 1.0, 0.0, 0.0, 1.0 ),       // red
    color4( 1.0, 1.0, 0.0, 1.0 ),       // yellow
    color4( 0.0, 1.0, 0.0, 1.0 ),       // green
    color4( 0.0, 0.0, 1.0, 1.0 ),       // blue
    color4( 1.0, 0.0, 1.0, 1.0 ),       // magenta
    color4( 0.0, 1.0, 1.0, 1.0 ),       // cyan
    color4( 1.0, 1.0, 1.0, 1.0 )        // white
};


point4 points[MAX_NUM_PARTICLES + 24];
color4 point_colors[MAX_NUM_PARTICLES + 24];

GLuint program;
mat4 model_view;
mat4 projection;

GLuint buffer;
GLuint loc, loc2;
GLint model_view_loc, projection_loc;

/* particle struct */

typedef struct particle {
    int color;
    point4 position;
    vec4 velocity;
    float mass;
} particle;

particle particles[MAX_NUM_PARTICLES];       /* particle system */

/* initial state of particle system */

int present_time;
int last_time;
int num_particles = INITIAL_NUM_PARTICLES;
float point_size = INITIAL_POINT_SIZE;
float speed = INITIAL_SPEED;
bool gravity = FALSE;            /* gravity off */
bool elastic = FALSE;            /* restitution off */
bool repulsion = FALSE;          /* repulsion off */
float coef = 1.0;                 /* perfectly elastic collisions */
float d2[MAX_NUM_PARTICLES][MAX_NUM_PARTICLES];   /* array for interparticle distances */


//----------------------------------------------------------------------------

static int Index = 0;

void
quad( int a, int b, int c, int d )
{
    point_colors[Index] = vertex_colors[0]; points[Index] = vertices[a]; Index++;
    point_colors[Index] = vertex_colors[0]; points[Index] = vertices[b]; Index++;
    point_colors[Index] = vertex_colors[0]; points[Index] = vertices[c]; Index++;
    point_colors[Index] = vertex_colors[0]; points[Index] = vertices[d]; Index++;
}

//----------------------------------------------------------------------------

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


void
init( void )
{
    colorcube();

    /* set up particles with random locations and velocities */
    for ( int i = 0; i < num_particles; i++ ) {
        particles[i].mass = 1.0;
        particles[i].color = i % NUM_COLORS;
        for ( int j = 0; j < 3; j++ ) {
            particles[i].position[j] =
                2.0 * ( ( float ) rand() / RAND_MAX ) - 1.0;
            particles[i].velocity[j] =
                speed * 2.0 * ( ( float ) rand() / RAND_MAX ) - 1.0;
        }
        particles[i].position[3] = 1.0;
    }

    // Create a vertex array object
    GLuint vao;
    glGenVertexArraysAPPLE( 1, &vao );
    glBindVertexArrayAPPLE( vao );

    // Create and initialize a buffer object
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(point_colors),
		  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(point_colors), point_colors );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader91.glsl", "fshader91.glsl" );
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

    model_view_loc = glGetUniformLocation( program, "ModelView" );
    projection_loc = glGetUniformLocation( program, "Projection" );

    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    glPointSize( point_size );
}

//----------------------------------------------------------------------------

float
forces( int i, int j )
{
    int k;
    float force = 0.0;
    if ( gravity && j == 1 )
        force = -1.0;           /* simple gravity */
    if ( repulsion )
        for ( k = 0; k < num_particles; k++ ) { /* repulsive force */
            if ( k != i )
                force +=
                    0.001 * ( particles[i].position[j] -
                              particles[k].position[j] ) / ( 0.001 +
                                                             d2[i][k] );
        }
    return ( force );
}

//----------------------------------------------------------------------------

void
collision( int n )

/* tests for collisions against cube and reflect particles if necessary */
{
    int
        i;
    for ( i = 0; i < 3; i++ ) {
        if ( particles[n].position[i] >= 1.0 ) {
            particles[n].velocity[i] = -coef * particles[n].velocity[i];
            particles[n].position[i] =
                1.0 - coef * ( particles[n].position[i] - 1.0 );
        }
        if ( particles[n].position[i] <= -1.0 ) {
            particles[n].velocity[i] = -coef * particles[n].velocity[i];
            particles[n].position[i] =
                -1.0 - coef * ( particles[n].position[i] + 1.0 );
        }
    }
}

//----------------------------------------------------------------------------

void
idle( void )
{
    int
        i,
        j,
        k;
    float
        dt;
    present_time = glutGet( GLUT_ELAPSED_TIME );
    dt = 0.001 * ( present_time - last_time );
    for ( i = 0; i < num_particles; i++ ) {
        for ( j = 0; j < 3; j++ ) {
            particles[i].position[j] += dt * particles[i].velocity[j];
            particles[i].velocity[j] +=
                dt * forces( i, j ) / particles[i].mass;
        }
        collision( i );
    }
    if ( repulsion )
        for ( i = 0; i < num_particles; i++ )
            for ( k = 0; k < i; k++ ) {
                d2[i][k] = 0.0;
                for ( j = 0; j < 3; j++ )
                    d2[i][k] += ( particles[i].position[j] -
                                  particles[k].position[j] ) *
                        ( particles[i].position[j] -
                          particles[k].position[j] );
                d2[k][i] = d2[i][k];
            }
    last_time = present_time;
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void
menu( int option )
{
    switch ( option ) {
	case 1:
            num_particles *= 2;
            break;

	case 2:
            num_particles /= 2;
            break;

	case 3:
            speed *= 2.0;
            break;

	case 4:
            speed /= 2.0;
            break;

	case 5:
            point_size *= 2.0;
            break;

	case 6:
            point_size /= 2.0;
            if ( point_size < 1.0 )
                point_size = 1.0;
            break;

	case 7:
            gravity = !gravity;
            break;

	case 8:
            elastic = !elastic;
	    coef = elastic ? 0.9 : 1.0;
            break;

	case 9:
            repulsion = !repulsion;
            break;

	case 10:
            exit( EXIT_SUCCESS );
            break;
    }

    init();

    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );

    for ( int i = 0; i < num_particles; i++ ) {
        point_colors[i + 24] = vertex_colors[particles[i].color];
        // particles[i].position[3] = 1.0;
        points[i + 24] = particles[i].position;
    }

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(point_colors), point_colors );
    glDrawArrays( GL_POINTS, 24, num_particles );
    for ( int i = 0; i < 6; i++ )
        glDrawArrays( GL_LINE_LOOP, i * 4, 4 );
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
    
    point4 eye = vec4( 1.5, 1.0, 1.0, 1.0 );
    point4 at = vec4( 0.0, 0.0, 0.0, 1.0 );
    vec4 up = vec4( 0.0, 1.0, 0.0, 1.0 );

    mat4 projection = Ortho( -2.0, 2.0, -2.0, 2.0, -4.0, 4.0 );
    mat4 model_view = LookAt( eye, at, up );

    glUniformMatrix4fv( model_view_loc, 1, GL_TRUE, model_view );
    glUniformMatrix4fv( projection_loc, 1, GL_TRUE, projection );
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "particle system" );

    glutCreateMenu( menu );
    glutAddMenuEntry( "more particles", 1 );
    glutAddMenuEntry( "fewer particles", 2 );
    glutAddMenuEntry( "faster", 3 );
    glutAddMenuEntry( "slower", 4 );
    glutAddMenuEntry( "larger particles", 5 );
    glutAddMenuEntry( "smaller particles", 6 );
    glutAddMenuEntry( "toggle gravity", 7 );
    glutAddMenuEntry( "toggle restitution", 8 );
    glutAddMenuEntry( "toggle repulsion", 9 );
    glutAddMenuEntry( "quit", 10 );
    glutAttachMenu( GLUT_MIDDLE_BUTTON );

    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutIdleFunc( idle );

    glutMainLoop();
    return 0;
}
