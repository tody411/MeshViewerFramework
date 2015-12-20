uniform int textureNo;
uniform sampler2D tex;
uniform float constantAlpha;

void main (void)
{
	vec4 color = vec4(gl_TexCoord[0].st, textureNo / 5.0, 1.0);
	vec4 texColor = texture2D(tex, gl_TexCoord[0].st);
	gl_FragColor = color;
	gl_FragColor.a = (1.0 - constantAlpha) * texColor.a + constantAlpha;
}