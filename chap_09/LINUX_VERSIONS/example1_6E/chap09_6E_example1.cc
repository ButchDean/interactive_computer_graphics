/* Particles in a box */

#define MAX_NUM_PARTICLES 1000
#define INITIAL_NUM_PARTICLES 25
#define INITIAL_POINT_SIZE 5.0
#define INITIAL_SPEED 1.0
#define NUM_COLORS 8

#define TRUE 1
#define FALSE 0

#include <Angel.h>

typedef vec4  point4;
typedef vec4  color4;

point4 vertices[8] = {point4(-1.1,-1.1,1.1, 1.0),point4(-1.1,1.1,1.1, 1.0),
   point4(1.1,1.1,1.1, 1.0), point4(1.1,-1.1,1.1, 1.0), point4(-1.1,-1.1,-1.1, 1.0),
   point4(-1.1,1.1,-1.1, 1.0), point4(1.1,1.1,-1.1, 1.0), point4(1.1,-1.1,-1.1, 1.0)};


color4 colors[8] = {point4(0.0,0.0,0.0, 1.0),point4(1.0,0.0,0.0, 1.0),
   point4(1.0,1.0,0.0, 1.0), point4(0.0,1.0,0.0, 1.0), point4(0.0,0.0,1.0, 1.0),
   point4(1.0,0.0,1.0, 1.0), point4(0.0,1.0,1.0, 1.0), point4(1.0,1.0,1.0, 1.0)};


/* rehaping routine called whenever window is resized or moved */

point4 points[MAX_NUM_PARTICLES+24];
color4 point_colors[MAX_NUM_PARTICLES+24];

GLuint program;
mat4 model_view;
mat4 projection;

GLuint buffers[2];
GLuint loc, loc2;
GLint model_view_loc, projection_loc;

void quad(int a, int b, int c, int d)
{
     static int i =0; /* vertex and color index */
     point_colors[i] = colors[0];
     points[i] = vertices[a];
     i++;
     point_colors[i] = colors[0];
     points[i] = vertices[b];
     i++;
     point_colors[i] = colors[0];
     points[i] = vertices[c];
     i++;
     point_colors[i] = colors[0];
     points[i] = vertices[d];
     i++;
     i=i%24;
}

void colorcube()
{
   quad(1,0,3,2);
   quad(2,3,7,6);
   quad(3,0,4,7);
   quad(6,5,1,2);
   quad(4,5,6,7);
   quad(5,4,0,1);
}

/* globals */

/* particle struct */

typedef struct particle
{ 
     int color;
     point4 position;
     vec4 velocity;
     float mass;
} particle;

particle particles[MAX_NUM_PARTICLES]; /* particle system */

/* initial state of particle system */

int present_time;
int last_time;
int num_particles = INITIAL_NUM_PARTICLES;
float point_size = INITIAL_POINT_SIZE;
float speed = INITIAL_SPEED;
bool gravity = FALSE; /* gravity off */
bool elastic = FALSE; /* restitution off */
bool repulsion = FALSE; /* repulsion off */
float coef = 1.0; /* perfectly elastic collisions */
float d2[MAX_NUM_PARTICLES][MAX_NUM_PARTICLES]; /* array for interparticle distances */

GLsizei wh = 500, ww = 500; /* initial window size */


void myReshape(int w, int h)
{

/* adjust clipping box */

        point4 eye = vec4(1.5, 1.0, 1.0, 1.0);
        point4 at = vec4(0.0, 0.0, 0.0, 1.0);
        vec4 up =  vec4(0.0, 1.0, 0.0, 1.0); 
        projection = Ortho(-2.0, 2.0, -2.0, 2.0, -4.0, 4.0);
        model_view = LookAt(eye, at, up);
        glUniformMatrix4fv(model_view_loc, 16, GL_TRUE, model_view);
        glUniformMatrix4fv(projection_loc, 16, GL_TRUE, projection);

       

/* adjust viewport and  clear */

        if(w<h) glViewport(0,0,w,w);
        else glViewport(0,0,h,h);


/* set global size for use by drawing routine */

        ww = w;
        wh = h; 
}

void myinit()
{
        int  i, j;

 colorcube();

 /* set up particles with random locations and velocities */

        for(i=0; i<num_particles; i++) 
        {
            particles[i].mass = 1.0;
            particles[i].color = i%NUM_COLORS;
            for(j=0; j<3; j++)
            {
                particles[i].position[j] = 2.0*((float) rand()/RAND_MAX)-1.0;
                particles[i].velocity[j] = speed*2.0*((float) rand()/RAND_MAX)-1.0;
            }
            particles[i].position[3] = 1.0;
        }
        glPointSize(point_size);


/* set clear color to grey */

   glClearColor(0.5, 0.5, 0.5, 1.0);

   loc = glGetAttribLocation(program, "vPosition");
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, points);
   loc2 = glGetAttribLocation(program, "vColor");  //vertex color in shader
   glEnableVertexAttribArray(loc2);
   glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, point_colors);
   model_view_loc = glGetUniformLocation(program, "model_view");
   projection_loc = glGetUniformLocation(program, "projection");

/* set up vertex buffer object */

   glGenBuffers(1, buffers);
   glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(points), NULL, GL_DYNAMIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(point_colors), point_colors, GL_DYNAMIC_DRAW);
}

float forces(int i, int j)
{
   int k;
   float force = 0.0;
   if(gravity&&j==1) force = -1.0; /* simple gravity */
   if(repulsion) for(k=0; k<num_particles; k++)  /* repulsive force */
   {
      if(k!=i) force+= 0.001*(particles[i].position[j]-particles[k].position[j])/(0.001+d2[i][k]);
   }
   return(force);
}

void collision(int n)

/* tests for collisions against cube and reflect particles if necessary */

{
     int i;
     for (i=0; i<3; i++) 
     {
           if(particles[n].position[i]>=1.0) 
           {
                particles[n].velocity[i] = -coef*particles[n].velocity[i];
                particles[n].position[i] = 1.0-coef*(particles[n].position[i]-1.0);
           }
           if(particles[n].position[i]<=-1.0) 
           {
                particles[n].velocity[i] = -coef*particles[n].velocity[i];
                particles[n].position[i] = -1.0-coef*(particles[n].position[i]+1.0);
           }
     }
}
void myIdle()
{
    int i, j, k;
    float dt;
    present_time = glutGet(GLUT_ELAPSED_TIME);
    dt = 0.001*(present_time -  last_time);
    for(i=0; i<num_particles; i++)
    {
       for(j=0; j<3; j++)
       {
           particles[i].position[j]+=dt*particles[i].velocity[j];
           particles[i].velocity[j]+=dt*forces(i,j)/particles[i].mass;
       }
        collision(i);
    }
    if(repulsion) for(i=0;i<num_particles;i++) for(k=0;k<i;k++)
    {
            d2[i][k] = 0.0;
            for(j=0;j<3;j++) d2[i][k]+= (particles[i].position[j]-
              particles[k].position[j])*(particles[i].position[j]-
              particles[k].position[j]);
            d2[k][i]=d2[i][k];
    }
    last_time = present_time;
    glutPostRedisplay();
}


void main_menu(int index)
{
   switch(index)
   {
      case(1):
	{
                num_particles = 2*num_particles;
                myinit();
                break;
     	}
	case(2):
	{
                num_particles = num_particles/2;
                myinit();
		break;
	}
	case(3):
	{
                speed = 2.0*speed;
                myinit();
		break;
	}
        case(4):
        {
                speed = speed/2.0;
                myinit();
                break;
        }
        case(5):
        {
                point_size = 2.0*point_size;
                myinit();
                break;
        }
        case(6):
        {
                point_size = point_size/2.0;
                if(point_size<1.0) point_size = 1.0;
                myinit();
                break;
        }
        case(7):
        {
                gravity = !gravity;
                myinit();
                break;
        }
        case(8):
        {
                elastic = !elastic;
                if(elastic) coef = 0.9;
                  else coef = 1.0;
                myinit();
                break;
        }
        case(9):
        {
                repulsion = !repulsion;
                myinit();
                break;
        }
	case(10):
	{
		exit(0);
		break;
	}
   }
}

void myDisplay()
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    for(i=0; i<num_particles; i++)
    {
       point_colors[i+24] = colors[particles[i].color];
      // particles[i].position[3] = 1.0;
       points[i+24] = particles[i].position;
    }
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point_colors), point_colors, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_POINTS, 24, num_particles);
    for(i=0; i<6; i++) glDrawArrays(GL_LINE_LOOP, i*4, 4);
    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow("particle system");
    glutDisplayFunc(myDisplay);
    glewInit();
    program = InitShader("vshader91.glsl", "fshader91.glsl");
    myinit ();

    glutCreateMenu(main_menu);
    glutAddMenuEntry("more particles", 1);
    glutAddMenuEntry("fewer particles", 2);
    glutAddMenuEntry("faster", 3);
    glutAddMenuEntry("slower", 4);
    glutAddMenuEntry("larger particles", 5);
    glutAddMenuEntry("smaller particles", 6);
    glutAddMenuEntry("toggle gravity",7);
    glutAddMenuEntry("toggle restitution",8);
    glutAddMenuEntry("toggle repulsion",9);
    glutAddMenuEntry("quit",10);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutIdleFunc(myIdle);
    glutReshapeFunc (myReshape); 
    glutMainLoop();
}
