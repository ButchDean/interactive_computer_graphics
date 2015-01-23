attribute  vec4 vPosition;
attribute  vec4 vColor;
varying vec4 color;

void main() 
{
  gl_Position = vPosition;
  color = vColor;
} 
