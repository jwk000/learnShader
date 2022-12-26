#version 410

uniform samplerCube cubemap;//立方体采样器，接收texture

in vec3 fragPos;//采样向量
out vec4 outCol;

void main(){
    outCol = texture(cubemap, fragPos);//3维向量采样
}