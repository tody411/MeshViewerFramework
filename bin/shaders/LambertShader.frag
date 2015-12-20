uniform sampler2D normalTex;

void main (void)
{
	vec4 N_color = texture2D(normalTex, gl_TexCoord[0].st);
	vec3 N = normalize( 2.0 * N_color.xyz - vec3(1.0, 1.0, 1.0) );

	vec3 L = gl_LightSource[0].position.xyz;
	vec4 Ka = gl_LightSource[0].ambient;
	vec4 Kd = gl_LightSource[0].diffuse;

    float LdN = clamp(dot( L, N ), 0.0, 1.0);
	vec4 c = Ka + Kd * LdN;

	float alpha = N_color.a;
	c.a = min(alpha, c.a);

	gl_FragColor = c;
}