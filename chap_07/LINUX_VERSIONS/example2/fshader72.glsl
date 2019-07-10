#version 150

attribute  vec3 R;
uniform samplerCube texMap;
varying vec4 fColor;

void main()
{
     vec4 texColor = textureCube(texMap, R);

    fColor = texColor;
}
