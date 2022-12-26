#version 410

layout(location=0) in vec3 position;
layout(location=1) in vec4 color;
layout(location=3) in vec2 uv;

out vec4 fragColor;
out vec2 fragUV;

void main()
{
    gl_Position = vec4(position, 1.0);
    fragColor = color;
    fragUV = vec2(uv.x,1-uv.y);//opengl的纹理是从下往上存储的
}