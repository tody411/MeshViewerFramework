varying vec3 Nw;

void main(void)
{
    Nw = normalize(gl_NormalMatrix * gl_Normal);
	gl_Position =  ftransform();
}