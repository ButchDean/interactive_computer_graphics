// Sphere approximation by recursive subdivision of a tetrahedron

#include "Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


#define N 4  // number of subdivisions
#define M 16*64*3  // number of resulting points

GLsizei w=512, h=512;


point4 data[M];

// four equally spaced points on the unit circle

point4 v[4]= {vec4(0.0, 0.0, 1.0, 1.0), vec4(0.0, 0.942809, -0.333333, 1.0),
                vec4(-0.816497, -0.471405, -0.333333, 1.0),
               vec4(0.816497, -0.471405, -0.333333, 1.0)};

float theta = 0.0;
float phi = 0.0;
float radius = 2.0;

GLuint program;

GLuint buffers[1];
GLuint loc ;
GLint matrix_loc, projection_loc;

static int k =0;

point4 at = vec4(0.0, 0.0, 0.0, 1.0);
point4 eye = vec4(0.0, 0.0, 2.0, 1.0);
vec4 up = vec4(0.0, 1.0, 0.0, 0.0);

GLfloat left= -2.0, right=2.0, top=2.0, bottom= -2.0, near= -4.0, far=4.0;

mat4 model_view;
mat4 projection;

// move a point to unit circle

point4 unit(const point4 &p)
{
  point4 c;
  double d=0.0;
  for(int i=0; i<3; i++) d+=p[i]*p[i];
  d=sqrt(d);
  if(d > 0.0) for(int i=0; i<3; i++) c[i] = p[i]/d;
  c[3] = 1.0;
  return c;
}

void triangle( point4  a, point4 b, point4 c)
{
     data[k]= a;
     k++;
     data[k] = b;
     k++;
     data[k] = c;
     k++;
}


void divide_triangle(point4 a, point4 b, point4 c, int n)
{
 point4 v1, v2, v3;
 if(n>0)
 {
   v1 = unit(a + b);
   v2 = unit(a + c);
   v3 = unit(b + c);   
   divide_triangle(a ,v2, v1, n-1);
   divide_triangle(c ,v3, v2, n-1);
   divide_triangle(b ,v1, v3, n-1);
   divide_triangle(v1 ,v2, v3, n-1);
 }
 else triangle(a, b, c);
}

void tetrahedron(int n)
{
   divide_triangle(v[0], v[1], v[2] , n);
   divide_triangle(v[3], v[2], v[1], n );
   divide_triangle(v[0], v[3], v[1], n );
   divide_triangle(v[0], v[3], v[2], n );
}





/* OpenGL initialization */

void init()
{

   tetrahedron(N);

    // Create a vertex array object

    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object

/* set up vertex buffer object */

   glGenBuffers(1, buffers);
   glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    // Load shaders and use the resulting shader program

    program = InitShader("vshader51.glsl", "fshader51.glsl");
    glUseProgram(program);

   loc = glGetAttribLocation(program, "vPosition");
   
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, 0);

   matrix_loc = glGetUniformLocation(program, "model_view");
   projection_loc = glGetUniformLocation(program, "projection");



   glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
}

void display()
{
     vec4 t;
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  /*clear the window */
     eye[0] = radius*sin(theta)*cos(phi);
     eye[1] = radius*sin(theta)*sin(phi);
     eye[2] = radius*cos(theta);
     model_view =  LookAt(eye, at, up);
     projection = Ortho(left, right, bottom, top, near, far);
     glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, model_view);
     glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);
     for(int i = 0; i<M; i+=3) glDrawArrays(GL_LINE_LOOP, i, 3); 
     glutSwapBuffers();
}



void mykey(unsigned char key, int mousex, int mousey)
{
   float dr = 3.14159/180.0*5.0;
   if(key=='q'||key=='Q') exit(0);
   if(key == 'x') {left *= 1.1; right *= 1.1; }
   if(key == 'X') {left *= 0.9; right *= 0.9; }
   if(key == 'y') {bottom *= 1.1; top *= 1.1; }
   if(key == 'Y') {bottom *= 0.9; top *= 0.9; }
   if(key == 'z') {near  *= 1.1; far *= 1.1;}
   if(key == 'Z') {near *= 0.9; far *= 0.9;}
   if(key == 'r') radius *= 2.0;
   if(key == 'R') radius *= 0.5;
   if(key == 'o') theta += dr;
   if(key == 'O') theta -= dr;
   if(key == 'p') phi += dr;
   if(key == 'P') phi -= dr;
   glutPostRedisplay();
}

void reshape(GLsizei ww, GLsizei hh)
{
   glViewport(0,0, ww, hh);
   w = ww;
   h = hh;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);

    glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow("Color Cube");

	glewInit();
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(mykey);


    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
