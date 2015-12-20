varying vec3 Nw;

void main (void)
{
    vec3 N = normalize( Nw );
    vec3 Nc = 0.5 * N + vec3(0.5, 0.5, 0.5);
    gl_FragColor = vec4(Nc, 1.0);
}