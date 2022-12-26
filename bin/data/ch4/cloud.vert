#version 410

layout(location=0) in vec3 pos;
layout(location=3) in vec2 uv;

uniform vec3 movepos;
uniform vec3 scale;

out vec2 fragUV;

void main(){
    gl_Position=vec4(pos*scale+movepos,1);
    fragUV=vec2(uv.x,1-uv.y);
}