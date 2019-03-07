#include <Angel.h>

#define N 36

typedef Angel::vec4 point4;

GLuint program;

GLuint texMapLocation;

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;

GLuint ctm_loc, projection_loc;
vec4 viewer = vec4(0.0, 0.0, 1.0, 0.0);
mat4 ctm;
mat4 projection;


GLuint buffers[1];
GLuint loc, loc2;


point4  vertices[8] = {point4(-0.5,-0.5,0.5, 1.0),point4(-0.5,0.5,0.5, 1.0),
   point4(0.5,0.5,0.5, 1.0), point4(0.5,-0.5,0.5, 1.0), point4(-0.5,-0.5,-0.5, 1.0),
   point4(-0.5,0.5,-0.5, 1.0), point4(0.5,0.5,-0.5, 1.0), point4(0.5,-0.5,-0.5, 1.0)};

point4 points[N];
point4 normals[N];

vec4 normal;
vec3 normal3;

GLuint tex[1];

void quad(int a, int b, int c, int d)
{
     static int i =0;

     normal3 = cross(vertices[b] - vertices[a],
        vertices[c]  - vertices[a]);
     normal = vec4(normal3[0], normal3[1], normal3[2], 0.0);


     normals[i] = normal;
     points[i] = vertices[a];
     i++;
     normals[i] = normal;
     points[i] = vertices[b];
     i++;
     normals[i] = normal;
     points[i] = vertices[c];
     i++;
     normals[i] = normal;
     points[i] = vertices[a];
     i++;
     normals[i] = normal;
     points[i] = vertices[c];
     i++;
     normals[i] = normal;
     points[i] = vertices[d];
     i++;
     i%=N;
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


void display( void )
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  /*clear the window */
     ctm = RotateX(theta[0])*RotateY(theta[1])*RotateZ(theta[2]);
     glUniformMatrix4fv(ctm_loc, 1, GL_TRUE, ctm);
     glDrawArrays(GL_TRIANGLES, 0, N);
     glutSwapBuffers();
}


void spinCube()
{


	theta[axis] += 0.005;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{

	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    if (w <= h)
        //projection = Ortho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            //2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
        // projection = Ortho(-0.4, 0.4, -0.4 * (GLfloat) h / (GLfloat) w,
            // 0.4 * (GLfloat) h / (GLfloat) w, 0.0, 10.0);
        projection = Frustum(-0.4, 0.4, -0.4 * (GLfloat) h / (GLfloat) w,
            0.4 * (GLfloat) h / (GLfloat) w, 0.1, 1.0);
    else
        // projection = Ortho(-2.0 * (GLfloat) w / (GLfloat) h,
            // 2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
        //projection = Ortho(-0.4 * (GLfloat) w / (GLfloat) h,
            //0.4 * (GLfloat) w / (GLfloat) h, -0.4, 0.4, 0.0, 10.0);
        projection = Ortho(-0.4 * (GLfloat) w / (GLfloat) h,
            0.4 * (GLfloat) w / (GLfloat) h, -0.4, 0.4, 0.1, 1.0);
     glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);
}

void key(unsigned char k, int x, int y)
{
	if(k == '1') glutIdleFunc(spinCube);
	if(k == '2') glutIdleFunc(NULL);
        if(k == 'q') exit(0);
}

void init()
{

    colorcube();

    GLubyte red[3] = {255, 0, 0};
    GLubyte green[3] = {0, 255, 0};
    GLubyte blue[3] = {0, 0, 255};
    GLubyte cyan[3] = {0, 255, 255};
    GLubyte magenta[3] = {255, 0, 255};
    GLubyte yellow[3] = {255, 255, 0};

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP);

   glGenTextures(1, tex);
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_CUBE_MAP, tex[0]);

   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, red);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, green);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, blue);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, cyan);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, magenta);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, yellow);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

   loc = glGetAttribLocation(program, "vPosition");
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 4, GL_FLOAT, GL_TRUE, 0, points);
   loc2 = glGetAttribLocation(program, "Normal");
   glEnableVertexAttribArray(loc2);
   glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_TRUE, 0, normals);
   ctm_loc = glGetUniformLocation(program, "ModelView");
   projection_loc = glGetUniformLocation(program, "Projection");

   glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);

    /* set up uniform parameter */

    texMapLocation = glGetUniformLocation(program, "texMap");
    glUniform1i(texMapLocation, tex[0]);

    glGenBuffers(1, buffers);
    glBindBuffer( GL_ARRAY_BUFFER, buffers[0]);
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(normals),
                  NULL, GL_DYNAMIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(normals), normals );


   glClearColor(1.0,1.0,1.0,1.0);
}

int
main(int argc, char **argv)
{
    colorcube();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow("colorcube");


    glewInit();

    program  = InitShader("vshader72.glsl", "fshader72.glsl");

    init();

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouse);

    glutKeyboardFunc(key);
    glutMainLoop();
    return 0;
}
