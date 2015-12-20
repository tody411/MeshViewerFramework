varying vec3 Nw;
uniform float border;

void main (void)
{
	vec3 N = normalize( Nw );

	vec3 L = normalize(gl_LightSource[0].position.xyz);
	float Ka = gl_LightSource[0].ambient.x;
	float Kd = gl_LightSource[0].diffuse.x;

	//float I = Ka + Kd * dot( L, N );
	float I = dot( L, N );

    float t = smoothstep(border-0.05, border+0.05, I);

    vec4 c1 = vec4(0.1, 0.1, 0.4, 1.0);
    vec4 c2 = vec4(0.3, 0.3, 0.8, 1.0);


	vec4 c = mix(c1, c2, t);

	gl_FragColor = c;
}