in vec3 L;
in vec3 V;
uniform sampler2D texMap;
in vec2 st;
uniform vec4 DiffuseProduct;

out vec4 fColor;

void main()
{

   vec4 N = texture2D(texMap, st);
   vec3 NN =  normalize(2.0*N.xyz-1.0);
   vec3 LL = normalize(L);
   float Kd = max(dot(NN.xyz, LL), 0.0);
   fColor = Kd*DiffuseProduct;
}
