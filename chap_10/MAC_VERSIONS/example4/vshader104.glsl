varying vec4 color;
attribute vec4 vPosition;
uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform vec4 LightPosition;
uniform float Shininess;
void main()
{
    vec4 ambient, diffuse, specular;
    gl_Position = vPosition;
    vec3 N =normalize(vPosition.xyz);
    vec3 L = normalize(LightPosition.xyz - vPosition.xyz);
    if(LightPosition.w == 0.0) L = normalize(LightPosition.xyz); 
    vec3 E = normalize(vPosition.xyz);
    vec3 H = normalize(L+E);
    float Kd = max(dot(L, N), 0.0);
    Kd = dot(L, N);
    float Ks = pow(max(dot(N, H), 0.0), Shininess);
    ambient = AmbientProduct;
    diffuse = Kd*DiffuseProduct;
    if(dot(L, N) < 0.0) specular = vec4(0.0, 0.0, 0.0, 1.0);
    else specular = Ks*SpecularProduct;
    color = vec4((ambient + diffuse + specular).xyz, 1.0);
}

