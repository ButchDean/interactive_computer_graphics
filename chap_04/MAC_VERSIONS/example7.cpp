#include "Angel.h"

GLsizei w=512, h=512;

typedef Angel::vec4 point4;

float theta = 0.0;
float phi = 0.0;
float radius = 1.0;

GLuint buffers[1];
GLuint loc ;
GLint matrix_loc, projection_loc, color_loc;

point4 triangles [3*464*2*435];


point4 white = vec4(1.0, 1.0, 1.0, 1.0);
point4 black = vec4(0.0, 0.0, 0.0, 1.0);

point4 at = vec4(0.0, 0.0, 0.0, 1.0);
point4 eye = vec4(0.0, 0.0, 0.0, 1.0);
vec4 up = vec4(0.0, 1.0, 0.0, 0.0);

GLfloat left= -1.0, right=1.0, top=1.0, bottom= -1.0, near= 0.5, far=3.0;

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


/* set up vertex buffer object */

   glGenBuffers(1, buffers);
   glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);

    program = InitShader("vshader47.glsl", "fshader47.glsl");
    glUseProgram(program);

   loc = glGetAttribLocation(program, "vPosition");
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
   matrix_loc = glGetUniformLocation(program, "model_view");
   projection_loc = glGetUniformLocation(program, "projection");
   color_loc = glGetUniformLocation(program, "fcolor");

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1.0, 1.0);
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
     projection = Frustum(left, right, bottom, top, near, far);
     projection = Perspective(45.0, 1.0, near, far);
     glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, model_view);
     glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     glUniform4fv(color_loc, 1, white);
     glDrawArrays(GL_TRIANGLES, 0, 3*435*464*2); 
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
     glUniform4fv(color_loc, 1, black);
     glDrawArrays(GL_TRIANGLES, 0, 3*435*464*2); 
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
    float data[465][436];
    int k=0;
    int i, j;
    int n, m;
    float fn, fm, fmax;
    FILE *fp;
    fp = fopen("honolulu.raw", "r");
    fscanf(fp, "%d %d", &n, &m);
    fn = n;
    fm = m;
    for(i=0; i<n; i++) for(j=0; j<m;j++) fscanf(fp, "%f", &data[i][j]);
    float max = data[0][0];
    for(i=0; i<n; i++) for(j=0; j<m;j++) if(data[i][j]>max) max=data[i][j];
    fmax = max;
    for(i=0; i<n-1; i++) for(j=0; j<m-1;j++) 
    {
        triangles[k] = vec4(4.0*2.0*(i/fn-0.5), 0.3*data[i][j]/fmax, -4.0*j/fm, 1.0); 
        k++;
        triangles[k] = vec4(4.0*2.0*((i+1)/fn-0.5), 0.3*data[i+1][j]/fmax, -4.0*j/fm, 1.0); 
        k++;
        triangles[k] = vec4(4.0*2.0*((i+1)/fn-0.5), 0.3*data[i+1][j+1]/fmax, -4.0*(j+1)/fm, 1.0); 
        k++;
        triangles[k] = vec4(4.0*2.0*((i+1)/fn-0.5), 0.3*data[i+1][j]/fmax, -4.0*j/fm, 1.0); 
        k++;
        triangles[k] = vec4(4.0*2.0*((i+1)/fn-0.5), 0.3*data[i+1][j+1]/fmax, -4.0*(j+1)/fm, 1.0); 
        k++;
        triangles[k] = vec4(4.0*2.0*(i/fn-0.5), 0.3*data[i][j+1]/fmax, -4.0*(j+1)/fm, 1.0); 
        k++;
    }
    printf("%d %d %d\n", n, m, k);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Color Cube");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(mykey);

    init();

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
