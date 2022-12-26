#version 410

uniform mat4 mvp;
uniform mat4 model;
uniform mat3 normal;
uniform float t;

layout(location=0) in vec3 pos;
layout(location=1) in vec4 tan;
layout(location=2) in vec3 nrm;
layout(location=3) in vec2 uv;

//out vec3 fragNrm;
out vec3 fragWorldPos;
out vec2 fragUV;
out vec2 fragUV2;
out mat3 TBN;

void main(){
    gl_Position=mvp*vec4(pos,1);
    fragUV=vec2(uv.x+t*0.05,uv.y)*3;
    fragUV2=vec2(uv.x,uv.y+t*0.02f)*2;
    fragWorldPos=(model*vec4(pos,1)).xyz;
    //fragNrm=(normal*nrm).xyz;

    vec3 T = normalize(normal*tan.xyz);
    vec3 B = normalize(normal*cross(tan.xyz,nrm));
    vec3 N = normalize(normal*nrm);
    TBN=mat3(T,B,N);
}