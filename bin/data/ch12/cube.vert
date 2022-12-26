#version 410

uniform mat4 mvp;

layout(location=0)in vec3 pos;
out vec3 fragPos;

void main(){
    fragPos = pos;
    gl_Position=(mvp*vec4(pos,1)).xyww;//令z=w则透视投影位于视锥最远的位置
}