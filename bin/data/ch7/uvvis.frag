#version 410

in vec3 fragNrm;

out vec4 outCol;

void main()
{
	outCol = vec4(fragNrm, 1.0);
}
