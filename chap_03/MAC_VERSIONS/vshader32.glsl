attribute vec4 vColor;
attribute vec4 vPosition;

varying vec4 color;

void main() 
{
  gl_Position = vPosition;
  color = vColor;
} 
