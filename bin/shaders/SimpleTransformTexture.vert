
uniform mat4 matrix;

void main(void)
{
	gl_Position =  matrix * gl_Vertex;
	gl_TexCoord[0]=gl_MultiTexCoord0;
}