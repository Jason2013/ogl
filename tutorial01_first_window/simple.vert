#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 Color0;

layout(location = 0) out vec3 vColor0;

void main()
{
    gl_Position = vec4(vPos, 1.0);
    vColor0 = Color0;
}
