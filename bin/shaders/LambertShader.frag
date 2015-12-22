varying vec3 Nw;

void main (void)
{
	vec3 N = normalize( Nw );

	vec3 L = normalize(gl_LightSource[0].position.xyz);
	vec4 Ka = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;
	vec4 Kd = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;

	float Id = dot( L, N );
	Id = max(Id, 0.0);

	vec4 c = Ka + Kd * Id;
	c = clamp(c, 0.0, 1.0);
	gl_FragColor = c;
}