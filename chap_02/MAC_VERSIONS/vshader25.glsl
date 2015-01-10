uniform mat4  Proj;

attribute vec4 vPosition;

void
main()
{
     gl_Position = Proj * vPosition;
}
