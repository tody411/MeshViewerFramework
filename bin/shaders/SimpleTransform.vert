varying vec3 Nw;
varying vec3 Vw;

void main(void)
{
    Vw = normalize((gl_ModelViewMatrix * gl_Vertex).xyz);
    Nw = normalize(gl_NormalMatrix * gl_Normal);
	gl_Position =  ftransform();
}