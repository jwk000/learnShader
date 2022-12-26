#version 410

uniform sampler2D tex;
in vec2 fragUV;

out vec4 outColor;

void main(){
    outColor=texture(tex,fragUV);
    if(outColor.a<1) discard;
}