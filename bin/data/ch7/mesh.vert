#version 410

uniform mat4 mvp;
uniform mat3 normal;
uniform mat4 model;

layout(location=0) in vec3 pos;
layout(location=2) in vec3 nrm;

out vec3 fragNrm;
out vec3 fragWorldPos;
void main(){
    gl_Position = mvp * vec4(pos,1);
    fragNrm=(normal*nrm).xyz;
    fragWorldPos=(model*vec4(pos,1)).xyz;
}