/* bump map vertex shader */

#version 150

out vec3 L; /* light vector in texture-space coordinates */
out vec3 V; /* view vector in texture-space coordinates */

in vec2 texcoord;
in vec4 vPosition;

uniform vec4 Normal;
uniform vec4 LightPosition;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 NormalMatrix;
uniform vec3 objTangent; /* tangent vector in object coordinates */

out vec2 st;

void main()
{
    mat3 NM3;

    NM3[0][0] = NormalMatrix[0][0];
    NM3[0][1] = NormalMatrix[0][1];
    NM3[0][2] = NormalMatrix[0][2];
    NM3[1][0] = NormalMatrix[1][0];
    NM3[1][1] = NormalMatrix[1][1];
    NM3[1][2] = NormalMatrix[1][2];
    NM3[2][0] = NormalMatrix[2][0];
    NM3[2][1] = NormalMatrix[2][1];
    NM3[2][2] = NormalMatrix[2][2];

    gl_Position = Projection*ModelView*vPosition;


    st = texcoord;

    vec3 eyePosition = vec3(ModelView*vPosition);
    vec3 eyeLightPos = (ModelView*LightPosition).xyz;

   /* normal, tangent and binormal in eye coordinates */

    vec3 N = normalize(NM3*Normal.xyz);
    vec3 T  = normalize(NM3*objTangent);
    vec3 B = cross(N, T);

    /* light vector in texture space */

    L.x = dot(T, eyeLightPos-eyePosition);
    L.y = dot(B, eyeLightPos-eyePosition);
    L.z = dot(N, eyeLightPos-eyePosition);

    L = normalize(L);

    /* view vector in texture space */

    V.x = dot(T, -eyePosition);
    V.y = dot(B, -eyePosition);
    V.z = dot(N, -eyePosition);

    V = normalize(V);
}
