varying  vec4 color;
varying  vec2 texCoord;

uniform sampler2D texture;

void main() 
{ 
    gl_FragColor = color * texture2D( texture, texCoord );
} 

