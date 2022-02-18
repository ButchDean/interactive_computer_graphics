#version 150

out vec3 R;
in  vec4 vPosition;
in  vec4 Normal;

uniform mat4 ModelView;
uniform mat4 Projection;


void main()
{
    gl_Position = Projection*ModelView*vPosition;

    vec4 eyePos  = ModelView*vPosition;
    
    vec4 NN = ModelView*Normal;
    vec3 N =NN.xyz;
    R = reflect(eyePos.xyz, N);


}
