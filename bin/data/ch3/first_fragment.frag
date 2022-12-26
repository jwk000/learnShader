#version 410

uniform sampler2D saimaTex;

in vec4 fragColor;
in vec2 fragUV;

out vec4 outColor;

void main()
{
    outColor = texture(saimaTex, fragUV);
}