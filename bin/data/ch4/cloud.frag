#version 410

uniform sampler2D tex;
in vec2 fragUV;

out vec4 outColor;

void main(){
    outColor=texture(tex,fragUV);
    outColor.a=min(outColor.a,0.8);
}