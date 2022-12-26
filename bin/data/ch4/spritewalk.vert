#version 410

uniform vec2 size; //一个精灵的大小（缩放比例）
uniform vec2 offset;//精灵在图片的位置
uniform mat4 model;//模型变换
uniform mat4 view;//摄像机视图变换
uniform mat4 proj;//投影变换

layout(location=0) in vec3 pos;
layout(location=3) in vec2 uv;

out vec2 fragUV;

void main(){
    gl_Position= proj*view*model*vec4(pos,1); //mat4可以乘vec4
    fragUV=vec2(uv.x+offset.x,1-uv.y+offset.y)*size;
}