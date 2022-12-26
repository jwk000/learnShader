#version 410

uniform sampler2D saimaTex1;
uniform sampler2D saimaTex2;

uniform float brightness;

in vec2 fragUV;
out vec4 outColor;

void main()
{
    vec4 tex1 = texture(saimaTex1, fragUV) ;
    vec4 tex2 = texture(saimaTex2, fragUV);
    
    outColor = mix(tex1,tex2,brightness);
}