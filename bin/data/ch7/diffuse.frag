#version 410

uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 meshCol;
uniform vec3 camPos;

in vec3 fragNrm;
in vec3 fragWorldPos;
out vec4 outCol;

void main(){
    vec3 normal = normalize(fragNrm);
    float lightAmt = dot(normal,lightDir);//强度
    vec3 light=lightCol*lightAmt;//去除负数

    float dim = 1-max(0,dot(normal,normalize(camPos-fragWorldPos)));
    dim = pow(dim,4);

    outCol=vec4(light*meshCol+dim,1);
}