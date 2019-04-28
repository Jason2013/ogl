#version 330 core

layout(location = 0) in vec3 vColor0;
layout(location = 0) out vec4 vColor;

void main()
{
    vColor = vec4(vColor0, 1.0);
}
