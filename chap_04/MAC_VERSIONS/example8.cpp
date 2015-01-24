// Projective shadow example

#include "Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


GLsizei w=512, h=512;

float theta = 0.0;
float phi = 0.0;
float radius = 1.0;

GLuint buffers[1];
GLuint loc ;
GLint matrix_loc, projection_loc, color_loc;

point4 square[4] = {vec4(-0.5, 0.5, -0.5, 1.0), vec4(-0.5, 0.5, 0.5, 1.0), vec4(0.5, 0.5, -0.5, 1.0), vec4(0.5, 0.5, 0.5, 1.0)};

float light[3] = {0.0, 2.0, 0.0}; //initial light position


mat4 m;

point4 red = vec4(1.0, 0.0, 0.0, 1.0);
point4 black = vec4(0.0, 0.0, 0.0, 1.0);

point4 at = vec4(0.0, 0.0, 0.0, 1.0);
point4 eye = vec4(1.0, 1.0, 1.0, 1.0);
vec4 up = vec4(0.0, 1.0, 0.0, 0.0);

GLfloat left= -4.0, right=4.0, top=4.0, bottom= -4.0, near= -5.0, far=5.0;

mat4 model_view;
mat4 projection;


GLuint program;

/* OpenGL initialization */

void init()
{

 // Create a vertex array object
    GLuint vao;
    glGenVertexArraysAPPLE( 1, &vao );
    glBindVertexArrayAPPLE( vao );

/* set up buffer object */

   glGenBuffers(1, buffers);
   glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

   program = InitShader("vshader48.glsl", "fshader48.glsl");
   glUseProgram( program );

   loc = glGetAttribLocation(program, "vPosition");
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, 0);
   matrix_loc = glGetUniformLocation(program, "model_view");
   projection_loc = glGetUniformLocation(program, "projection");
   color_loc = glGetUniformLocation(program, "fcolor");

   for(int i =0; i<4; i++) for(int j =0; j<4;j++) m[i][j] = 0.0;
   m[0][0] = m[1][1] = m[2][2] = 1.0;
   m[3][1] = -1.0/light[1];

   glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
}

void display()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  /*clear the window */
     model_view =  LookAt(eye, at, up);
     projection = Ortho(left, right, bottom, top, near, far);


     glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, model_view);
     glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);

// Draw rectangle in red

     glUniform4fv(color_loc, 1, red);
     glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); 

// rotate light

     light[0] = 1.0*sin((6.28/180.0)*theta);
     light[2] = 1.0*cos((6.28/180.0)*theta);
     
// alter model-view matrix for projection
// draw projected shadow in black

     model_view = model_view*Translate(light[0], light[1], light[2])*m*Translate(-light[0], -light[1], -light[2]);
     glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, model_view);
     glUniform4fv(color_loc, 1, black);
     glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); 
     glutSwapBuffers();
}



void mykey(unsigned char key, int mousex, int mousey)
{
   if(key=='q'||key=='Q') exit(0);
}


// rotate light position

void myidle()
{
   theta+=0.1;
   if(theta>360.0) theta-=360;
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
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Shadows");
    glutIdleFunc(myidle);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(mykey);

    init();

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
