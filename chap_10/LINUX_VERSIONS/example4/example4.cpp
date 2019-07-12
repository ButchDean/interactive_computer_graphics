
#define N 10000

#include "Angel.h"

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

point4 points[N];

GLuint program;

GLuint buffer;
GLuint loc;

GLuint ambient_product_loc, diffuse_product_loc, specular_product_loc;
GLuint light_position_loc;
GLuint shininess_loc;
vec4 ambient_product, diffuse_product, specular_product;

vec4 viewer = vec4(0.0, 0.0, 1.0, 0.0);
point4 light_position = point4(0.0, 0.0, -10.0, 0.0);
color4 light_ambient = color4(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse = color4(1.0, 1.0, 1.0, 1.0);
color4 light_specular = color4(1.0, 1.0, 1.0, 1.0);

color4 material_ambient = color4(1.0, 0.0, 1.0, 1.0);
color4 material_diffuse = color4(1.0, 0.8, 0.0, 1.0);
color4 material_specular = color4(1.0, 0.8, 0.0, 1.0);
float material_shininess = 100.0;

vec4 product(vec4 a, vec4 b)
{
   return vec4(a[0]*b[0], a[1]*b[1], a[2]*b[2], a[3]*b[3]);
}


/* OpenGL initialization */

void init()
{
    int k;
    float theta, phi;



/* compute and store N points pn unit sphere */

    for( k=0; k<N; k++)
    {
         theta = 2.0*M_PI* float(random())/RAND_MAX;
         phi = M_PI*float(random())/RAND_MAX;
         points[k][0] = cos(theta)*sin(phi);
         points[k][1] = sin(theta)*sin(phi);
         points[k][2] = cos(phi);
         points[k][3] = 1.0;
     }

    // Create a vertex array object
    GLuint vao;
    glGenVertexArraysAPPLE( 1, &vao );
    glBindVertexArrayAPPLE( vao );


/* set up vertex buffer object */

   loc = glGetAttribLocation(program, "vPosition");
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, points);

   ambient_product_loc = glGetUniformLocation(program, "AmbientProduct");
   diffuse_product_loc = glGetUniformLocation(program, "DiffuseProduct");
   specular_product_loc = glGetUniformLocation(program, "SpecularProduct");
   shininess_loc = glGetUniformLocation(program, "Shininess");
   light_position_loc = glGetUniformLocation(program, "LightPosition");

   ambient_product = product(light_ambient, material_ambient);
   diffuse_product = product(light_diffuse, material_diffuse);
   specular_product = product(light_specular, material_specular);

   glUniform4fv(ambient_product_loc, 4, ambient_product);
   glUniform4fv(diffuse_product_loc, 4, diffuse_product);
   glUniform4fv(specular_product_loc, 4, specular_product);

   glUniform4fv(light_position_loc, 4, light_position);
   glUniform1f(shininess_loc, material_shininess);


   glGenBuffers(1, &buffer);
   glBindBuffer(GL_ARRAY_BUFFER, buffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

   glPointSize(3.0);
   glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */

}

void display( void )
{
     glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */
     glDrawArrays(GL_POINTS, 0, N); 
     glFlush();
}



int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Simple GLSL example");
    glutDisplayFunc(display);

    program = InitShader("vshader104.glsl", "fshader104.glsl");
    init();

    glutMainLoop();
    return 0;
}
