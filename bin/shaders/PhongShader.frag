varying vec3 Nw;
varying vec3 Vw;

void main (void)
{
	vec3 N = normalize( Nw );
    vec3 V = normalize( Vw );
	vec3 L = normalize(gl_LightSource[0].position.xyz);
    vec3 RV = reflect(-V, N);

	vec4 Ka = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;
	vec4 Kd = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;
    vec4 Ks = gl_LightSource[0].specular * gl_FrontMaterial.specular;
    float shininess = gl_FrontMaterial.shininess;

	float Id = dot( L, N );
	Id = max(Id, 0.0);

    float Is = dot( L, RV );
    Is = max(Is, 0.0);

    //Is = pow( Is, shininess);

	vec4 c = Ka + Kd * Id + Ks * Is;
	c = clamp(c, 0.0, 1.0);
	gl_FragColor = c;
}